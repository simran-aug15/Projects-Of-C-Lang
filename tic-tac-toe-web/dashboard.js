window.addEventListener('DOMContentLoaded', () => {
    const startButton = document.querySelector('#startButton');

    startButton.addEventListener('click', () => {
        window.location.href = 'game.html';
    });
});