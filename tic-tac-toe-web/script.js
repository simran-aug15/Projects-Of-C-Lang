const board = document.getElementById("board");
const statusText = document.getElementById("status");

const xScoreText = document.getElementById("xScore");
const oScoreText = document.getElementById("oScore");

let currentPlayer = "X";
let gameActive = true;

let xScore = 0;
let oScore = 0;

let gameState = ["", "", "", "", "", "", "", "", ""];

const winConditions = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6]
];

/* Create Board */
function createBoard() {
  board.innerHTML = "";

  gameState.forEach((cell, index) => {
    const div = document.createElement("div");

    div.classList.add("cell");

    /* Add X or O color classes */
    if (cell === "X") {
      div.classList.add("x");
    }

    if (cell === "O") {
      div.classList.add("o");
    }

    div.dataset.index = index;
    div.innerText = cell;

    div.addEventListener("click", handleMove);

    board.appendChild(div);
  });
}

/* Handle Player Move */
function handleMove(e) {
  const index = e.target.dataset.index;

  if (gameState[index] !== "" || !gameActive) {
    return;
  }

  gameState[index] = currentPlayer;

  e.target.innerText = currentPlayer;

  /* Add X and O color classes dynamically */
  e.target.classList.add(
    currentPlayer === "X" ? "x" : "o"
  );

  checkWinner();
}

/* Check Winner */
function checkWinner() {
  let won = false;
  let winningCells = [];

  for (let condition of winConditions) {
    const [a, b, c] = condition;

    if (
      gameState[a] &&
      gameState[a] === gameState[b] &&
      gameState[a] === gameState[c]
    ) {
      won = true;

      winningCells = [a, b, c];

      break;
    }
  }

  /* Winner Found */
  if (won) {
    statusText.innerText =
      `Player ${currentPlayer} wins 🎉`;

    gameActive = false;

    /* Update Score */
    if (currentPlayer === "X") {
      xScore++;
      xScoreText.innerText = xScore;
    } else {
      oScore++;
      oScoreText.innerText = oScore;
    }

    /* Highlight Winning Cells */
    const cells = document.querySelectorAll(".cell");

    winningCells.forEach(index => {
      cells[index].classList.add("winner");
    });

    return;
  }

  /* Draw Match */
  if (!gameState.includes("")) {
    statusText.innerText = "It's a draw 🤝";

    gameActive = false;

    return;
  }

  /* Switch Player */
  currentPlayer = currentPlayer === "X"
    ? "O"
    : "X";

  statusText.innerText =
    `Player ${currentPlayer}'s Turn`;
}

/* Restart Game */
function restartGame() {
  currentPlayer = "X";

  gameActive = true;

  gameState = ["", "", "", "", "", "", "", "", ""];

  statusText.innerText = "Player X's Turn";

  createBoard();
}

/* Reset Scores */
function resetScores() {
  xScore = 0;
  oScore = 0;

  xScoreText.innerText = 0;
  oScoreText.innerText = 0;

  restartGame();
}

/* Initial Board Load */
createBoard();const board = document.getElementById("board");
const statusText = document.getElementById("status");

const xScoreText = document.getElementById("xScore");
const oScoreText = document.getElementById("oScore");

let currentPlayer = "X";
let gameActive = true;

let xScore = 0;
let oScore = 0;

let gameState = ["", "", "", "", "", "", "", "", ""];

const winConditions = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6]
];

/* Create Board */
function createBoard() {
  board.innerHTML = "";

  gameState.forEach((cell, index) => {
    const div = document.createElement("div");

    div.classList.add("cell");

    /* Add X or O color classes */
    if (cell === "X") {
      div.classList.add("x");
    }

    if (cell === "O") {
      div.classList.add("o");
    }

    div.dataset.index = index;
    div.innerText = cell;

    div.addEventListener("click", handleMove);

    board.appendChild(div);
  });
}

/* Handle Player Move */
function handleMove(e) {
  const index = e.target.dataset.index;

  if (gameState[index] !== "" || !gameActive) {
    return;
  }

  gameState[index] = currentPlayer;

  e.target.innerText = currentPlayer;

  /* Add X and O color classes dynamically */
  e.target.classList.add(
    currentPlayer === "X" ? "x" : "o"
  );

  checkWinner();
}

/* Check Winner */
function checkWinner() {
  let won = false;
  let winningCells = [];

  for (let condition of winConditions) {
    const [a, b, c] = condition;

    if (
      gameState[a] &&
      gameState[a] === gameState[b] &&
      gameState[a] === gameState[c]
    ) {
      won = true;

      winningCells = [a, b, c];

      break;
    }
  }

  /* Winner Found */
  if (won) {
    statusText.innerText =
      `Player ${currentPlayer} wins 🎉`;

    gameActive = false;

    /* Update Score */
    if (currentPlayer === "X") {
      xScore++;
      xScoreText.innerText = xScore;
    } else {
      oScore++;
      oScoreText.innerText = oScore;
    }

    /* Highlight Winning Cells */
    const cells = document.querySelectorAll(".cell");

    winningCells.forEach(index => {
      cells[index].classList.add("winner");
    });

    return;
  }

  /* Draw Match */
  if (!gameState.includes("")) {
    statusText.innerText = "It's a draw 🤝";

    gameActive = false;

    return;
  }

  /* Switch Player */
  currentPlayer = currentPlayer === "X"
    ? "O"
    : "X";

  statusText.innerText =
    `Player ${currentPlayer}'s Turn`;
}

/* Restart Game */
function restartGame() {
  currentPlayer = "X";

  gameActive = true;

  gameState = ["", "", "", "", "", "", "", "", ""];

  statusText.innerText = "Player X's Turn";

  createBoard();
}

/* Reset Scores */
function resetScores() {
  xScore = 0;
  oScore = 0;

  xScoreText.innerText = 0;
  oScoreText.innerText = 0;

  restartGame();
}

/* Initial Board Load */
createBoard();
