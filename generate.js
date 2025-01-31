export function generateRandomLevel(percentage, money) {
    const startMoney = !isNaN(money) ? Math.min(Math.max(money, 200), 100000) : 5000;
    
    const content = startMoney + '\n';
    const totalCells = 15 * 7;
    const cellsToFill = Math.round(totalCells * (percentage / 100));
    const colors = ['Z', 'M', 'R', 'C', 'E'];
    const filledCells = new Set();

    let result = content;

    for (let i = 0; i < cellsToFill; i++) {
        let row, col;
        do {
            row = Math.floor(Math.random() * 7) + 1;
            col = Math.floor(Math.random() * 15) + 1;
        } while (filledCells.has(`${row},${col}`));

        filledCells.add(`${row},${col}`);
        const randomColor = colors[Math.floor(Math.random() * colors.length)];
        result += `${col} ${row} ${randomColor}\n`;
    }

    return result;
}