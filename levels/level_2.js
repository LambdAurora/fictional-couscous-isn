level.player_position(-1, 0.5)
  .background("#6b6e65");

level.register_wall(
  new Wall(0, 0, 0, 1)
  .color("#b0acb8")
  .checkerboard()
);

level.register_wall(
  new Wall(0, 2, 0, 4)
  .color("#b0acb8")
  .checkerboard()
);

level.register_wall(
  new Wall(-1, 4, -5, 4)
  .color("#b0acb8")
);

level.register_wall(
  new Wall(-5, 4, -5, 3)
  .color("#b0acb8")
);

level.register_wall(
  new Wall(-5, 2, -5, 0)
  .color("#b0acb8")
);

level.register_wall(
  new Wall(-5, 0, -4, 0)
  .color("#b0acb8")
);

level.register_wall(
  new Wall(-3, 0, 0, 0)
  .color("#b0acb8")
  .checkerboard()
);

level.register_wall(
  new Wall(0, 1, 0, 2)
  .color("#b6c4be")
  .bounce()
);

level.register_wall(
  new Wall(-5, 3, -5, 2)
  .color("#b6c4be")
  .bounce()
);

let wall_teleport_1 = new Wall(-3, 0, -4, 0);
let wall_teleport_2 = new Wall(0, 4, -1, 4);

wall_teleport_1.teleport(wall_teleport_2);
wall_teleport_2.teleport(wall_teleport_1);

level.register_wall(wall_teleport_1);
level.register_wall(wall_teleport_2);

level.register_wall(
  new Wall(-4.25, 3, -4, 3)
  .image("resources/flower.png", 0.5, 0.5)
);

level.register_wall(
  new Wall(-5, 2, 0, 2)
  .empty()
  .ghost()
);

level.register_room(
  new Room(-5, 0, 5, 2)
  .color("#657874")
);

level.register_room(
  new Room(-5, 2, 5, 2)
  .color("#646a73")
)
