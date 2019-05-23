module.exports.normalize = ([x, y]) => {
  let l = Math.sqrt(x*x + y*y);
  return [x/l, y/l];
}

module.exports.normal_vector = ([x, y]) => [-y, x];

module.exports.mult = ([x, y], by) => [x * by, y * by];

module.exports.add = ([x1, y1], [x2, y2]) => [x1 + x2, y1 + y2];
