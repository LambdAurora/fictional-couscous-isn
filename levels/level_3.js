level.player_position(1.5, 1.5)
  .background("#6b6e65");

level.register_wall(
  new Wall(3, 0, 3, 0.25)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

level.register_wall(
  new Wall(3, 3, 3, 2.75)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

level.register_wall(
  new Wall(0, 3, 0.25, 3)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

level.register_wall(
  new Wall(3, 3, 2.75, 3)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

level.register_wall(
  new Wall(3, 3, 3.25, 3)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

level.register_wall(
  new Wall(6, 3, 5.75, 3)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

level.register_wall(
  new Wall(3, 3, 3, 3.25)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

level.register_wall(
  new Wall(3, 6, 3, 5.75)
  .color("#5f5e61")
  .gradient("#6a6a6a")
);

// r1m1
level.register_wall(
  new Wall(0, 0, 0.5, 0)
  .color("#a47774")
  .checkerboard()
);

// r1m1
level.register_wall(
  new Wall(0.5, 0, 2.5, 0)
  .color("#e3cae9")
  .bounce()
);

// r1w2
level.register_wall(
  new Wall(2.5, 0, 3, 0)
  .color("#a47774")
  .checkerboard()
);

// r1w3
level.register_wall(
  new Wall(0, 0, 0, 3)
  .color("#a47774")
  .checkerboard()
);

// r2w1
level.register_wall(
  new Wall(0, 3, 0, 6)
  .color("#8aab96")
  .checkerboard()
);

// r2w2
level.register_wall(
  new Wall(0, 6, 3, 6)
  .color("#8aab96")
  .checkerboard()
);

// r3w1
level.register_wall(
  new Wall(3, 0, 6, 0)
  .color("#7e91b1")
  .checkerboard()
);

// r3w2
level.register_wall(
  new Wall(6, 0, 6, 3)
  .color("#7e91b1")
  .checkerboard()
);

let wall_teleport_1 = new Wall(3, 3.25, 3, 5.75);
let wall_teleport_2 = new Wall(3.25, 3, 5.75, 3);

wall_teleport_1.teleport(wall_teleport_2);
wall_teleport_2.teleport(wall_teleport_1);

level.register_wall(wall_teleport_1);
level.register_wall(wall_teleport_2);

level.register_wall(
  new Wall(0.25, 0.25, 0.5, 0.25)
  .image("resources/flower.png")
  .ghost()
);

level.register_wall(
  new Wall(0.25, 3, 2.75, 3)
  .ghost()
  .empty()
);

level.register_wall(
  new Wall(3, 0.25, 3, 2.75)
  .ghost()
  .empty()
);

level.register_room(
  new Room(0, 0, 3, 3)
  .color("#e62020")
);

level.register_room(
  new Room(0, 3, 3, 3)
  .color("#20e620")
);

level.register_room(
  new Room(3, 0, 3, 3)
  .color("#2020e6")
);
