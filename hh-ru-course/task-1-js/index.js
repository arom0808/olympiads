const readline = require('readline').createInterface(process.stdin, process.stdout);
readline.on('line', (line) => {
    console.log(line);
    // Введенная строка в переменной line, тут можно написать решение и вывести его с помощью console.log
    // console.log(String(result));
    readline.close();
}).on('close', () => process.exit(0));