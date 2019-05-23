const fs = require("fs");
const path = require("path");
const transpile = require("./transpile");
const parse = require("./parse");
const fill_rooms = require("./fill_rooms");

global.PATH_PREFIX = "../";

let argv = process.argv;
global.input_dir = path.resolve(process.cwd(), argv[argv.length - 2]);
global.output_file = path.resolve(process.cwd(), argv[argv.length - 1]);

if (!fs.lstatSync(input_dir).isDirectory()) {
  console.error("Invalid input directory (first argument): " + input_dir);
  process.exit(1);
}

let files = fs.readdirSync(input_dir).filter((f) => f.endsWith(".js"));

console.log("Reading...");

let levels = parse(files);

console.log("Placing rooms...");

for (let level of levels) {
  fill_rooms(level);
}

console.log("Generating file...");

let output = transpile(levels);

console.log("Writing file...");

fs.writeFileSync(output_file, output, "utf8");

console.log("Done!");
