// Import readline for user input
const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

// Function to fetch weather data for a city
function getWeather(city) {
    const apiKey = '82005d27a116c2880c8f0fcb866998a0';
    fetch(`https://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=${apiKey}`)
        .then(response => response.json())
        .then(data => {
            // Check if the response contains weather data
            if (data.cod !== 200) {
                console.error('City not found:');
                return;
            }
            const temp = data.main.temp;
            const pressure = data.main.pressure;
            const humidity = data.main.humidity;
            const id = data.weather[0].id;
            const description = data.weather[0].description;
            const feels = data.main.feels_like;
            const country = data.sys.country;

            // Log the weather details to the console
            console.log(`${city}, ${country}`);
            console.log("Weather Details:");
            console.log("Temperature:", temp + "°C");
            console.log("Pressure:", pressure + " hPa");
            console.log("Humidity:", humidity + "%");
            console.log("Feels Like:", feels + "°C");
            console.log("Description:", description);

            // Log weather icon info instead of setting wIcon.src
            if (id === 800) {
                console.log("Clear");
            } else if (id >= 200 && id <= 232) {
                console.log("Storm");
            } else if (id >= 600 && id <= 622) {
                console.log("Snow");
            } else if (id >= 701 && id <= 781) {
                console.log("Haze");
            } else if (id >= 801 && id <= 804) {
                console.log("Cloud");
            } else if ((id >= 500 && id <= 531) || (id >= 300 && id <= 321)) {
                console.log("Rain");
            }
        })
        .catch(error => {
            console.error('Error fetching weather data:', error);
        });
}

// Ask user for city name and fetch weather
readline.question('Enter city name: ', city => {
    getWeather(city);
    readline.close();
});