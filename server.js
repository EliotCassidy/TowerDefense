const express = require('express');
const app = express();
const path = require('path');

app.use(express.static('.'));

function generateRandomLevel(percentage) {
    const value = 5000;
    let content = `${value}\n`;
    const totalCells = 15 * 7;
    const cellsToFill = Math.round(totalCells * (percentage / 100));
    const colors = ['Z', 'M', 'R', 'C', 'E'];
    const filledCells = new Set();

    for (let i = 0; i < cellsToFill; i++) {
        let row, col;
        do {
            row = Math.floor(Math.random() * 7) + 1;
            col = Math.floor(Math.random() * 15) + 1;
        } while (filledCells.has(`${row},${col}`));

        filledCells.add(`${row},${col}`);
        const randomColor = colors[Math.floor(Math.random() * colors.length)];
        content += `${col} ${row} ${randomColor}\n`;
    }

    return content;
}

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

app.get('/:percentage', (req, res) => {
    const percentage = parseInt(req.params.percentage);
    if (isNaN(percentage) || percentage < 0 || percentage > 100) {
        return res.status(400).send('Invalid percentage');
    }

    const content = generateRandomLevel(percentage);
    res.setHeader('Content-Type', 'text/plain');
    res.setHeader('Content-Disposition', 'attachment; filename=niveau.txt');
    res.send(content);
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});