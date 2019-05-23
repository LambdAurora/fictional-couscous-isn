const vec = require("./vec");
const EPSILON = 0.0001;

module.exports = (level) => {
  function find_room(x, y) {
    for (let n = 0; n < level._rooms.length; n++) {
      let room = level._rooms[n];
      if (x >= room.x && x <= room.x + room.w && y >= room.y && y <= room.y + room.h) return n;
    }
    return null;
  }

  function get_adjacent_rooms(wall) {
    let center = [(wall.x1 + wall.x2) / 2, (wall.y1 + wall.y2) / 2];
    let vector = vec.normalize([wall.x2 - wall.x1, wall.y2 - wall.y1]);
    let normal = vec.normal_vector(vector);
    let point_left = vec.add(vec.mult(normal, EPSILON), center);
    let point_right = vec.add(vec.mult(normal, -EPSILON), center);

    let room_left = find_room(...point_left);
    let room_right = find_room(...point_right);

    return [room_left, room_right];
  }

  for (let wall of level._walls) {

    if (wall.type && wall.type[0] === "BOUNCE") {
      let [left, right] = get_adjacent_rooms(wall);
      wall.room_right = left;
      wall.room_left = right;
    } else if (wall.type && wall.type[0] === "TELEPORT") {
      let [left, right] = get_adjacent_rooms(wall.type[1]);
      wall.room_right = right;
      wall.room_left = left;
    } else {
      let [left, right] = get_adjacent_rooms(wall);
      wall.room_left = left;
      wall.room_right = right;
    }
  }
}
