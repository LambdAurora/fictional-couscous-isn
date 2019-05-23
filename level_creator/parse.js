const path = require("path");

function parse_color(...c) {
  let red, green, blue;
  if (c.length === 1) {
    let parsed = /^#?([0-9a-fA-F]{2})([0-9a-fA-F]{2})([0-9a-fA-F]{2})$/.exec(c[0]);
    if (!parsed) throw new Error("Invalid color: " + c[0]);
    red = parseInt(parsed[1], 16);
    green = parseInt(parsed[2], 16);
    blue = parseInt(parsed[3], 16);
  } else if (c.length === 3) {
    red = c[0];
    green = c[1];
    blue = c[2];
  } else throw new Error("Invalid color arguments: " + c.join(","));
  return [red, green, blue];
}

global.Wall = class Wall {
  constructor(x1, y1, x2, y2) {
    this.x1 = x1;
    this.y1 = y1;
    this.x2 = x2;
    this.y2 = y2;
    this.texture = null;
    this.red = null;
    this.green = null;
    this.blue = null;
    this.type = null;
    this._ghost = false;
  }

  color(...c) {
    let [red, green, blue] = parse_color(...c);
    this.red = red;
    this.green = green;
    this.blue = blue;
    return this;
  }

  checkerboard() {
    this.texture = ["CHECKERBOARD"];
    return this;
  }

  gradient(...c) {
    this.texture = ["GRADIENT", ...parse_color(...c)];
    return this;
  }

  image(uri, width = 0.5, height = 0.5) {
    this.texture = ["IMAGE", `"` + path.join(PATH_PREFIX, uri).replace(/\\/g, "\\\\") + `"`, width, height];
    return this;
  }

  empty() {
    this.texture = ["EMPTY"];
    return this;
  }

  bounce() {
    this.type = ["BOUNCE"];
    return this;
  }

  teleport(wall) {
    this.type = ["TELEPORT", wall];
    return this;
  }

  transparent(opacity) {
    this.type = ["TRANSPARENT", opacity * 255];
    return this;
  }

  ghost() {
    this._ghost = true;
    return this;
  }
};

global.Room = class Room {
  constructor(x, y, w, h) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.red = 45;
    this.green = 43;
    this.blue = 42;
  }

  color(...c) {
    let [red, green, blue] = parse_color(...c);
    this.red = red;
    this.green = green;
    this.blue = blue;
    return this;
  }

  wall(ghost) {
    let f = ghost ? ((l) => l.ghost().empty()) : ((l) => l.color(this.red, this.green, this.blue));
    level.register_wall(f(new Wall(this.x, this.y, this.x + this.w, this.y)));
    level.register_wall(f(new Wall(this.x + this.w, this.y, this.x + this.w, this.y + this.h)));
    level.register_wall(f(new Wall(this.x + this.w, this.y + this.h, this.x, this.y + this.h)));
    level.register_wall(f(new Wall(this.x, this.y + this.h, this.x, this.y)));
    return this;
  }
}

module.exports = (files) => {
  let levels = [];

  for (let file of files) {
    global.level = {
      _name: file.slice(0, -3).toUpperCase(),
      _scale: 1,
      _walls: [],
      _rooms: [],
      _player_x: 0,
      _player_y: 0,
      _player_rot: 0,
      _bg_red: 128,
      _bg_green: 128,
      _bg_blue: 128,
      _ground: null,

      name(str) {
        this._name = str;
        return this;
      },

      register_wall(wall) {
        this._walls.push(wall);
        return this;
      },

      register_room(room) {
        this._rooms.push(room);
        return this;
      },

      player_position(x, y) {
        this._player_x = x;
        this._player_y = y;
        return this;
      },

      player_rotation(rot) {
        this._player_rot = rot;
        return this;
      },

      scale(x) {
        this._scale = x;
        return this;
      },

      background(...c) {
        let [red, green, blue] = parse_color(...c);
        this._bg_red = red;
        this._bg_green = green;
        this._bg_blue = blue;
        return this;
      },

      ground(...c) {
        this._ground = parse_color(...c);
        return this;
      }
    };
    file = path.resolve(input_dir, file);
    let res = require(file);
    levels.push(global.level);
  }

  return levels;
}
