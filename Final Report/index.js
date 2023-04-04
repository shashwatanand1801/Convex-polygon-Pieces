import infiles from './jsons/infiles.json' assert { type: "json" };
import outfiles from './jsons/outfiles.json' assert { type: "json" };
import input from './jsons/input.json' assert { type: "json" };
import timeVal from './jsons/time.json' assert { type: "json" };



const table = document.getElementById("table");


infiles.forEach((image, idx) => {

  var row = document.createElement("tr");
  
  var sno = document.createElement("td");
  sno.textContent = idx+1;
  row.appendChild(sno);

  var size = document.createElement("td");
  size.textContent = input[idx];
  row.appendChild(size);

  var incell = document.createElement("td");
  var inimg = document.createElement("img");
  inimg.src = infiles[idx];
  console.log(inimg.src)
  incell.appendChild(inimg);
  row.appendChild(incell);


  var outcell = document.createElement("td");
  var outimg = document.createElement("img");
  outimg.src = outfiles[idx];
  outcell.appendChild(outimg);
  row.appendChild(outcell);

  var time = document.createElement("td");
  time.textContent = timeVal[idx];
  row.appendChild(time);

  table.appendChild(row);

});

// var chartData = [['Size', 'Time']]

// timeVal.forEach((val, idx) => {
//     chartData.push([parseInt(input[idx]), parseInt(val)])
// })

// console.log(chartData);



// google.charts.load('current',{packages:['corechart']});
// google.charts.setOnLoadCallback(drawChart); 

// function drawChart() {
//     // Set Data
//     const data = google.visualization.arrayToDataTable(
//         chartData
//     );
//     // Set Options
//     const options = {
//       title: 'Input Size vs Time',
//       hAxis: {title: 'Miliseconds'},
//       vAxis: {title: 'No of vertices'},
//       legend: 'none'
//     };
//     // Draw Chart
//     const chart = new google.visualization.LineChart(document.getElementById('myChart'));
//     chart.draw(data, options);
//     }



// Define Data
var data = [{
  x: input,
  y: timeVal,
  mode:"lines"
}];

// Define Layout
var layout = {
  xaxis: {range: [0, Math.max(...input)+10], title: "Input Size (No. of vertices)"},
  yaxis: {range: [0, Math.max(...timeVal)+(Math.max(...timeVal)/10)], title: "Time (ms)"},  
  title: "Input Size vs Time"
};

// Display using Plotly
Plotly.newPlot("myPlot", data, layout);