const board = document.getElementById("board");
const statusText = document.getElementById("status");

const xScoreText = document.getElementById("xScore");
const oScoreText = document.getElementById("oScore");

/* Replay / Exit Menu Elements */
const gameMenu = document.getElementById("gameMenu");
const menuMessage = document.getElementById("menuMessage");

let currentPlayer = "X";
let gameActive = true;

let xScore = 0;
let oScore = 0;

let gameState = [
  "", "", "",
  "", "", "",
  "", "", ""
];

/* Winning Patterns */
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

/* =========================
   Create Board
========================= */
function createBoard() {

  board.innerHTML = "";

  gameState.forEach((cell, index) => {

    const div = document.createElement("div");

    div.classList.add("cell");

    /* Add X and O Colors */
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

/* =========================
   Handle Move
========================= */
function handleMove(e) {

  const index = e.target.dataset.index;

  /* Prevent Extra Clicks */
  if (
    gameState[index] !== "" ||
    !gameActive
  ) {
    return;
  }

  gameState[index] = currentPlayer;

  e.target.innerText = currentPlayer;

  /* Add Color Classes */
  e.target.classList.add(
    currentPlayer === "X"
      ? "x"
      : "o"
  );

  checkWinner();
}

/* =========================
   Check Winner
========================= */
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
      `Player ${currentPlayer} Wins 🎉`;

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
    const cells =
      document.querySelectorAll(".cell");

    winningCells.forEach(index => {

      cells[index]
        .classList.add("winner");

    });

    /* Show Replay Popup */
    setTimeout(() => {

      menuMessage.innerText =
        `Player ${currentPlayer} Wins 🎉`;

      gameMenu.classList.remove("hidden");

    }, 700);

    return;
  }

  /* Draw Match */
  if (!gameState.includes("")) {

    statusText.innerText =
      "It's a Draw 🤝";

    gameActive = false;

    /* Show Draw Popup */
    setTimeout(() => {

      menuMessage.innerText =
        "It's a Draw 🤝";

      gameMenu.classList.remove("hidden");

    }, 700);

    return;
  }

  /* Switch Player */
  currentPlayer =
    currentPlayer === "X"
      ? "O"
      : "X";

  statusText.innerText =
    `Player ${currentPlayer}'s Turn`;
}

/* =========================
   Restart Game
========================= */
function restartGame() {

  currentPlayer = "X";

  gameActive = true;

  gameState = [
    "", "", "",
    "", "", "",
    "", "", ""
  ];

  statusText.innerText =
    "Player X's Turn";

  /* Hide Replay Menu */
  gameMenu.classList.add("hidden");

  createBoard();
}

/* =========================
   Reset Scores
========================= */
function resetScores() {

  xScore = 0;
  oScore = 0;

  xScoreText.innerText = 0;
  oScoreText.innerText = 0;

  restartGame();
}

/* =========================
   Exit Game
========================= */
function exitGame() {

  gameMenu.classList.add("hidden");

  board.innerHTML = "";

  statusText.innerText =
    "Game Ended ❌";
}

/* =========================
   Initial Load
========================= */
createBoard();