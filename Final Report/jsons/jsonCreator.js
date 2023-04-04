const fs = require('fs');

var data = [];

var inFolder = '../images/input';
var outFolder = '../images/output';

var indata = fs.readdirSync(inFolder)
var outdata = fs.readdirSync(outFolder)

indata.forEach((data,idx)=>{
    indata[idx] = inFolder + "/"  + data
})

outdata.forEach((data, idx)=>{
    outdata[idx] = outFolder + "/" + data
})

console.log(indata)
console.log(outdata)

// data.forEach(function(img){
//     const newImage = document.createElement('img');
//     newImage.src = "images/" + img; // Just concatenate the path to the file name
//     newImage.setAttribute("alt", "Some ALT text"); // images require an ALT attribute to be valid
//     console.log(newImage)
//   });


// const files = {
//     input : indata,
//     output : outdata
// }

// const infiles = [indata]
// const outfiles = [outdata]

const infile_string = JSON.stringify(indata)
const outfile_string = JSON.stringify(outdata)

fs.writeFile("infiles.json", infile_string, function(err, result) {
    if(err) console.log('error', err);
})


fs.writeFile("outfiles.json", outfile_string, function(err, result) {
    if(err) console.log('error', err);
})