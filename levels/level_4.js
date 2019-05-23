const EPSILON = 0.0001;

level.player_position(4.375, -3.75);
level.player_rotation(Math.PI / 2);
level.scale(0.4);

let inner_left_1 = new Wall(-0.5, -1 + EPSILON, 0.5, -1 + EPSILON);
let inner_left_2 = new Wall(-0.5, 1 - EPSILON, 0.5, 1 - EPSILON, 0.5);

let inner_right_1 = new Wall(4, -1 + EPSILON, 5, -1 + EPSILON);
let inner_right_2 = new Wall(4, 4 - EPSILON, 5, 4 - EPSILON, 0.5);

let outer_left_1 = new Wall(-0.5, -1, 0.5, -1);
let outer_left_2 = new Wall(-0.5, 1, 0.5, 1, 0.5);

let outer_right_1 = new Wall(4, -1, 5, -1);
let outer_right_2 = new Wall(4, 4, 5, 4, 0.5);

outer_left_1.teleport(inner_right_1);
outer_left_2.teleport(inner_right_2);
inner_left_1.teleport(outer_right_1);
inner_left_2.teleport(outer_right_2);

outer_right_1.teleport(inner_left_1);
outer_right_2.teleport(inner_left_2);
inner_right_1.teleport(outer_left_1);
inner_right_2.teleport(outer_left_2);

level.register_wall(inner_left_1);
level.register_wall(inner_left_2);

level.register_wall(inner_right_1);
level.register_wall(inner_right_2);

level.register_wall(outer_left_1);
level.register_wall(outer_left_2);

level.register_wall(outer_right_1);
level.register_wall(outer_right_2);

// outer, left

level.register_wall(
  new Wall(-0.5, -1, -0.5, 1)
  .color("#0d4a37")
  .checkerboard()
);

level.register_wall(
  new Wall(0.5, -1, 0.5, 1)
  .color("#0d4a37")
  .checkerboard()
);

// inner, left
level.register_wall(
  new Wall(-0.5 + EPSILON, -1, -0.5 + EPSILON, 1)
  .color("#0d304a")
  .checkerboard()
);

level.register_wall(
  new Wall(0.5 - EPSILON, -1, 0.5 - EPSILON, 1)
  .color("#0d304a")
  .checkerboard()
);

// outer, right

level.register_wall(
  new Wall(4, -1, 4, 4)
  .color("#0d304a")
  .checkerboard()
);

level.register_wall(
  new Wall(5, -1, 5, 4)
  .color("#0d304a")
  .checkerboard()
);

// inner, right
level.register_wall(
  new Wall(4 + EPSILON, -1, 4 + EPSILON, 4)
  .color("#0d4a37")
  .checkerboard()
);

level.register_wall(
  new Wall(5 - EPSILON, -1, 5 - EPSILON, 4)
  .color("#0d4a37")
  .checkerboard()
);
