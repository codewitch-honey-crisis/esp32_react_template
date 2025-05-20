import './App.css'
const fetchData = () => {
  let data;
  const promise = fetch("./api/")
    .then((response) => response.json())
    .then((json) => (data = json));
  return {
    read() {
      if (!data) {
        throw promise; 
      }
      return data;
    },
  };
};
const esp32Data = fetchData();

export default function App() {
    const edata = esp32Data.read();
    return (
        <>
            <h1>Vite + React + ClASP + ESP32</h1>
            <br />
            <p>ESP-IDF Version: {edata.idf_version}</p>
        </>
  );
}
