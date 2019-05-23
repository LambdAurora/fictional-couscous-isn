module.exports = (levels) => {
  let output = "";

  function write(str) {
    output += "    " + str + " \\\n";
  }

  function begin_level(name) {
    output += `#define ${name} \\\n`;
  }

  function end_level() {
    output += `\n`;
  }

  for (let level of levels) {
    begin_level(level._name);

    write(`world.n_rooms = ${level._rooms.length};`);
    write(`world.rooms = (Room**)malloc(sizeof(Room*) * world.n_rooms);`);

    for (let x = 0; x < level._rooms.length; x++) {
      let room = level._rooms[x];
      write(`CREATE_ROOM(_r_${x}, ${room.x}, ${room.y}, ${room.w}, ${room.h})`);
      write(`ROOM_COLOR(_r_${x}, ${room.red}, ${room.green}, ${room.blue})`);
      write(`world.rooms[${x}] = &_r_${x};`);
    }

    write(`world.player_position = Vec2D_new(${level._player_x * level._scale}, ${level._player_y * level._scale});`);
    write(`world.player_angle = ${level._player_rot};`);
    write(`Color bg = Color_new(${level._bg_red}, ${level._bg_green}, ${level._bg_blue});`);
    write(`Lines lines;`);
    write(`lines.length = ${level._walls.length};`);
    write(`lines.lines = (Line2D*) malloc(sizeof(Line2D) * lines.length);`);
    write("");

    for (let x = 0; x < level._walls.length; x++) {
      let wall = level._walls[x];
      let name = "_w_" + x;
      write(`CREATE_LINE(${name}, ${wall.x1 * level._scale}, ${wall.y1 * level._scale}, ${wall.x2 * level._scale}, ${wall.y2 * level._scale})`);

      if (wall.red !== null) {
        write(`LINE_COLOR(${name}, ${wall.red}, ${wall.green}, ${wall.blue})`);
      }

      if (wall.type !== null && wall.type[0] !== "TELEPORT") {
        if (wall.type.length === 1) write(`LINE_${wall.type[0]}(${name})`);
        else write(`LINE_${wall.type[0]}(${name}, ${wall.type.slice(1).join(",")})`);
      }

      if (wall.texture !== null) {
        if (wall.texture.length === 1) write(`LINE_${wall.texture[0]}(${name})`);
        else write(`LINE_${wall.texture[0]}(${name}, ${wall.texture.slice(1).join(",")})`);
      }

      if (wall._ghost) {
        write(`LINE_GHOST(${name})`);
      }

      if (wall.room_left !== null && wall.room_right !== null) {
        write(`ROOMS_AROUND(_w_${x}, _r_${wall.room_left}, _r_${wall.room_right})`);
      } else if (wall.room_left !== null) {
        write(`ROOM_LEFT(_w_${x}, _r_${wall.room_left})`);
      } else if (wall.room_right !== null) {
        write(`ROOM_RIGHT(_w_${x}, _r_${wall.room_right})`);
      }

      write("");
    }

    for (let x = 0; x < level._walls.length; x++) {
      let wall = level._walls[x];
      if (wall.type !== null && wall.type[0] === "TELEPORT") {
        let target = level._walls.findIndex(w => w === wall.type[1]);
        if (!~target) throw new Error("Invalid teleport target: " + wall.type[1]);
        write(`LINE_TELEPORT(_w_${x}, _w_${target})`);
        write("");
      }
    }

    for (let x = 0; x < level._walls.length; x++) {
      write(`lines.lines[${x}] = _w_${x};`);
    }

    end_level();
  }

  return output;
}
