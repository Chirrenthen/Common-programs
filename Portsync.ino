// Code written by Chirrenthen
// Visit my portfolio - https://chirrenthen.netlify.app
// For more information visit -> https://www.patreon.com/posts/portsync-esp32-130918146

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <esp_system.h>
#if __has_include(<esp_random.h>)
#include <esp_random.h>
#endif

const char* AP_SSID = "Skmei";
const char* AP_PASSWORD = "babu";
const uint8_t AP_CHANNEL = 1;
const uint8_t AP_MAX_CLIENTS = 4;

const size_t MAX_MESSAGES = 40;
const size_t MAX_TEXT_BYTES = 600;
const size_t MAX_USER_BYTES = 16;

struct Message {
  String user;
  String text;
};

const IPAddress apIP(192, 168, 4, 1);
const IPAddress apMask(255, 255, 255, 0);

WebServer server(80);
DNSServer dns;

Message messages[MAX_MESSAGES];
uint32_t nextId = 1;
uint32_t floorId = 1;
uint32_t epoch = 1;

const char page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
<title>PortSync</title>
<style>
  * { box-sizing: border-box; }
  html, body { height: 100%; margin: 0; }
  body {
    display: flex;
    flex-direction: column;
    height: 100dvh;
    background: #fafafa;
    color: #1a1a1a;
    font-family: system-ui, -apple-system, "Segoe UI", sans-serif;
  }
  header {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 14px 16px;
    background: #fff;
    border-bottom: 1px solid #eee;
  }
  h1 { margin: 0; font-size: 17px; font-weight: 600; }
  .right { display: flex; align-items: center; gap: 14px; }
  .dot { width: 8px; height: 8px; border-radius: 50%; background: #ccc; }
  .dot.on { background: #34a853; }
  #clear {
    border: 0;
    background: none;
    color: #888;
    font-size: 14px;
    padding: 4px;
    cursor: pointer;
  }
  #chat {
    flex: 1;
    display: flex;
    flex-direction: column;
    gap: 6px;
    padding: 16px;
    overflow-y: auto;
  }
  #chat:empty::before {
    content: "No messages yet";
    margin: auto;
    color: #aaa;
    font-size: 14px;
  }
  .msg {
    max-width: 78%;
    padding: 8px 12px;
    border-radius: 16px;
    font-size: 15px;
    line-height: 1.35;
    overflow-wrap: anywhere;
    white-space: pre-wrap;
  }
  .me { align-self: flex-end; background: #1a73e8; color: #fff; border-bottom-right-radius: 4px; }
  .them { align-self: flex-start; background: #eee; border-bottom-left-radius: 4px; }
  form {
    display: flex;
    gap: 8px;
    padding: 10px 12px calc(10px + env(safe-area-inset-bottom));
    background: #fff;
    border-top: 1px solid #eee;
  }
  input {
    flex: 1;
    min-width: 0;
    padding: 10px 14px;
    border: 1px solid #ddd;
    border-radius: 20px;
    font-size: 16px;
    outline: none;
  }
  input:focus { border-color: #1a73e8; }
  button.send {
    padding: 0 18px;
    border: 0;
    border-radius: 20px;
    background: #1a73e8;
    color: #fff;
    font-size: 15px;
    cursor: pointer;
  }
</style>
</head>
<body>
<header>
  <h1>PortSync</h1>
  <div class="right">
    <span class="dot" id="dot"></span>
    <button id="clear" type="button">Clear</button>
  </div>
</header>
<main id="chat"></main>
<form id="form" autocomplete="off">
  <input id="text" type="text" maxlength="150" placeholder="Message" enterkeyhint="send">
  <button class="send" type="submit">Send</button>
</form>
<script>
  const chat = document.getElementById("chat");
  const dot = document.getElementById("dot");
  const input = document.getElementById("text");
  const clearBtn = document.getElementById("clear");

  let me = "";
  try { me = localStorage.getItem("ps_id") || ""; } catch (e) {}
  if (!me) {
    me = (Math.random().toString(36) + "00000000").slice(2, 10);
    try { localStorage.setItem("ps_id", me); } catch (e) {}
  }

  let after = 0;
  let epoch = null;
  let busy = false;
  let forceStick = false;
  let armed = 0;

  function addMessage(m) {
    const el = document.createElement("div");
    el.className = "msg " + (m.u === me ? "me" : "them");
    el.textContent = m.t;
    chat.appendChild(el);
  }

  async function poll() {
    if (busy) return;
    busy = true;
    try {
      const res = await fetch("/poll?after=" + after + "&epoch=" + (epoch || 0), { cache: "no-store" });
      if (!res.ok) throw new Error("bad status");
      const data = await res.json();
      let stick = forceStick || chat.scrollHeight - chat.scrollTop - chat.clientHeight < 80;
      if (data.epoch !== epoch) {
        chat.textContent = "";
        epoch = data.epoch;
        stick = true;
      }
      data.msgs.forEach(addMessage);
      after = data.last;
      if (data.msgs.length) {
        if (stick) chat.scrollTop = chat.scrollHeight;
        forceStick = false;
      }
      dot.className = "dot on";
    } catch (e) {
      dot.className = "dot";
    } finally {
      busy = false;
    }
  }

  async function loop() {
    await poll();
    setTimeout(loop, 1000);
  }

  document.getElementById("form").addEventListener("submit", async (e) => {
    e.preventDefault();
    const t = input.value.trim();
    if (!t) return;
    input.value = "";
    input.focus();
    try {
      const res = await fetch("/send", { method: "POST", body: new URLSearchParams({ u: me, t: t }) });
      if (!res.ok) throw new Error("bad status");
      forceStick = true;
    } catch (err) {
      if (!input.value) input.value = t;
    }
    poll();
  });

  clearBtn.addEventListener("click", async () => {
    if (!armed) {
      clearBtn.textContent = "Sure?";
      armed = setTimeout(() => {
        armed = 0;
        clearBtn.textContent = "Clear";
      }, 3000);
      return;
    }
    clearTimeout(armed);
    armed = 0;
    clearBtn.textContent = "Clear";
    try { await fetch("/clear", { method: "POST" }); } catch (e) {}
    poll();
  });

  loop();
</script>
</body>
</html>
)rawliteral";

String clip(String s, size_t limit) {
  s.trim();
  if (s.length() > limit) {
    size_t cut = limit;
    while (cut > 0 && ((uint8_t)s[cut] & 0xC0) == 0x80) cut--;
    s = s.substring(0, cut);
    s.trim();
  }
  return s;
}

void appendEscaped(String& out, const String& s) {
  for (size_t i = 0; i < s.length(); i++) {
    char c = s[i];
    if (c == '"' || c == '\\') {
      out += '\\';
      out += c;
    } else if (c == '\n') {
      out += "\\n";
    } else if ((uint8_t)c >= 0x20) {
      out += c;
    }
  }
}

void handleRoot() {
  server.sendHeader("Cache-Control", "no-store");
  server.send_P(200, "text/html", page);
}

void handlePoll() {
  uint32_t after = strtoul(server.arg("after").c_str(), nullptr, 10);
  uint32_t clientEpoch = strtoul(server.arg("epoch").c_str(), nullptr, 10);
  if (clientEpoch != epoch) after = 0;

  uint32_t first = after + 1;
  if (first < floorId) first = floorId;
  if (nextId > MAX_MESSAGES && first < nextId - MAX_MESSAGES) first = nextId - MAX_MESSAGES;

  String out;
  out.reserve(1024);
  out += "{\"epoch\":";
  out += String(epoch);
  out += ",\"last\":";
  out += String(nextId - 1);
  out += ",\"msgs\":[";

  bool firstItem = true;
  for (uint32_t id = first; id < nextId; id++) {
    const Message& m = messages[(id - 1) % MAX_MESSAGES];
    if (!firstItem) out += ',';
    firstItem = false;
    out += "{\"u\":\"";
    appendEscaped(out, m.user);
    out += "\",\"t\":\"";
    appendEscaped(out, m.text);
    out += "\"}";
  }
  out += "]}";

  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", out);
}

void handleSend() {
  String user = clip(server.arg("u"), MAX_USER_BYTES);
  String text = clip(server.arg("t"), MAX_TEXT_BYTES);
  if (user.length() == 0 || text.length() == 0) {
    server.send(400, "text/plain", "empty");
    return;
  }
  Message& m = messages[(nextId - 1) % MAX_MESSAGES];
  m.user = user;
  m.text = text;
  nextId++;
  server.send(200, "text/plain", "ok");
}

void handleClear() {
  floorId = nextId;
  epoch++;
  for (size_t i = 0; i < MAX_MESSAGES; i++) {
    messages[i].user = "";
    messages[i].text = "";
  }
  server.send(200, "text/plain", "ok");
}

void handleNotFound() {
  server.sendHeader("Location", String("http://") + apIP.toString() + "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);

  WiFi.persistent(false);
  WiFi.setAutoReconnect(false);
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_OFF);
  delay(100);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, apMask);
  if (!WiFi.softAP(AP_SSID, AP_PASSWORD, AP_CHANNEL, 0, AP_MAX_CLIENTS)) {
    Serial.println("Access point failed to start, restarting");
    delay(1000);
    ESP.restart();
  }

  epoch = (esp_random() & 0xFFFFFF) + 1;

  dns.start(53, "*", apIP);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/poll", HTTP_GET, handlePoll);
  server.on("/send", HTTP_POST, handleSend);
  server.on("/clear", HTTP_POST, handleClear);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println();
  Serial.println("==== PortSync ====");
  Serial.print("Wi-Fi:    ");
  Serial.println(AP_SSID);
  Serial.print("Password: ");
  Serial.println(AP_PASSWORD);
  Serial.print("Open:     http://");
  Serial.println(WiFi.softAPIP());
  Serial.println("==================");
}

void loop() {
  dns.processNextRequest();
  server.handleClient();
  delay(1);
}
