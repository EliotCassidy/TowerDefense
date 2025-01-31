export function generateRandomLevel(percentage, money) {
    const startMoney = Math.min(Math.max(money || 5000, 200), 100000);
    let content = startMoney.toString() + '\n';
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