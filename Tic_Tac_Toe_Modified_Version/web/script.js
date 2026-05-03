const boardElement = document.getElementById('board');
const cells = document.querySelectorAll('.cell');
const statusDisplay = document.getElementById('status');
const resetBtn = document.getElementById('reset-btn');
const difficultySelect = document.getElementById('difficulty');

const playerScoreEl = document.querySelector('#player-score .value');
const aiScoreEl = document.querySelector('#ai-score .value');
const drawScoreEl = document.querySelector('#draw-score .value');

let board = ['', '', '', '', '', '', '', '', ''];
let gameActive = true;
let currentPlayer = 'O'; // Player is O, AI is X
let scores = { O: 0, X: 0, draw: 0 };

const winningConditions = [
    [0, 1, 2], [3, 4, 5], [6, 7, 8], // Rows
    [0, 3, 6], [1, 4, 7], [2, 5, 8], // Cols
    [0, 4, 8], [2, 4, 6]             // Diagonals
];

function handleCellClick(e) {
    const clickedCell = e.target;
    const clickedCellIndex = parseInt(clickedCell.getAttribute('data-index'));

    if (board[clickedCellIndex] !== '' || !gameActive || currentPlayer !== 'O') return;

    makeMove(clickedCellIndex, 'O');
    
    if (gameActive) {
        statusDisplay.innerText = "AI is thinking...";
        setTimeout(aiMove, 500);
    }
}

function makeMove(index, player) {
    board[index] = player;
    cells[index].classList.add(player.toLowerCase());
    checkResult();
}

function aiMove() {
    if (!gameActive) return;

    const difficulty = difficultySelect.value;
    let moveIndex;

    if (difficulty === 'easy') {
        moveIndex = getRandomMove();
    } else if (difficulty === 'medium') {
        moveIndex = getMediumMove();
    } else {
        moveIndex = getBestMove(); // Minimax
    }

    if (moveIndex !== null) {
        makeMove(moveIndex, 'X');
        if (gameActive) {
            currentPlayer = 'O';
            statusDisplay.innerText = "Your Turn";
        }
    }
}

function getRandomMove() {
    const available = board.map((val, idx) => val === '' ? idx : null).filter(val => val !== null);
    return available.length > 0 ? available[Math.floor(Math.random() * available.length)] : null;
}

function getMediumMove() {
    // Try to win
    for (let cond of winningConditions) {
        const [a, b, c] = cond;
        if (board[a] === 'X' && board[b] === 'X' && board[c] === '') return c;
        if (board[a] === 'X' && board[c] === 'X' && board[b] === '') return b;
        if (board[b] === 'X' && board[c] === 'X' && board[a] === '') return a;
    }
    // Block player
    for (let cond of winningConditions) {
        const [a, b, c] = cond;
        if (board[a] === 'O' && board[b] === 'O' && board[c] === '') return c;
        if (board[a] === 'O' && board[c] === 'O' && board[b] === '') return b;
        if (board[b] === 'O' && board[c] === 'O' && board[a] === '') return a;
    }
    return getRandomMove();
}

// Minimax Algorithm
function getBestMove() {
    let bestScore = -Infinity;
    let move;
    for (let i = 0; i < 9; i++) {
        if (board[i] === '') {
            board[i] = 'X';
            let score = minimax(board, 0, false);
            board[i] = '';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

const scoresTable = { X: 10, O: -10, draw: 0 };

function minimax(board, depth, isMaximizing) {
    let result = checkWinnerRaw();
    if (result !== null) return scoresTable[result];

    if (isMaximizing) {
        let bestScore = -Infinity;
        for (let i = 0; i < 9; i++) {
            if (board[i] === '') {
                board[i] = 'X';
                let score = minimax(board, depth + 1, false);
                board[i] = '';
                bestScore = Math.max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        let bestScore = Infinity;
        for (let i = 0; i < 9; i++) {
            if (board[i] === '') {
                board[i] = 'O';
                let score = minimax(board, depth + 1, true);
                board[i] = '';
                bestScore = Math.min(score, bestScore);
            }
        }
        return bestScore;
    }
}

function checkWinnerRaw() {
    for (let cond of winningConditions) {
        const [a, b, c] = cond;
        if (board[a] && board[a] === board[b] && board[a] === board[c]) return board[a];
    }
    if (!board.includes('')) return 'draw';
    return null;
}

function checkResult() {
    let roundWon = false;
    let winner = null;

    for (let i = 0; i <= 7; i++) {
        const winCondition = winningConditions[i];
        let a = board[winCondition[0]];
        let b = board[winCondition[1]];
        let c = board[winCondition[2]];
        if (a === '' || b === '' || c === '') continue;
        if (a === b && b === c) {
            roundWon = true;
            winner = a;
            break;
        }
    }

    if (roundWon) {
        statusDisplay.innerText = winner === 'O' ? "You Won! 🎉" : "AI Won! 🤖";
        statusDisplay.style.color = winner === 'O' ? 'var(--accent-o)' : 'var(--accent-x)';
        scores[winner]++;
        updateScores();
        gameActive = false;
        return;
    }

    if (!board.includes('')) {
        statusDisplay.innerText = "It's a Draw! 🤝";
        scores.draw++;
        updateScores();
        gameActive = false;
        return;
    }
}

function updateScores() {
    playerScoreEl.innerText = scores.O;
    aiScoreEl.innerText = scores.X;
    drawScoreEl.innerText = scores.draw;
}

function restartGame() {
    board = ['', '', '', '', '', '', '', '', ''];
    gameActive = true;
    currentPlayer = 'O';
    statusDisplay.innerText = "Your Turn";
    statusDisplay.style.color = 'var(--text-dim)';
    cells.forEach(cell => {
        cell.classList.remove('x', 'o');
    });
}

cells.forEach(cell => cell.addEventListener('click', handleCellClick));
resetBtn.addEventListener('click', restartGame);
updateScores();
