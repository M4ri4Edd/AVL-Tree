const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

class Node {
    constructor(value) {
        this.value = value;
        this.left = null;
        this.right = null;
        this.height = 1;
    }
}

class AVL {
    constructor() {
        this.root = null;
    }

    getHeight(node) {
        if (node === null) return 0;
        return node.height;
    }

    getBalanceFactor(node) {
        if (node === null) return 0;
        return this.getHeight(node.left) - this.getHeight(node.right);
    }

    rightRotate(y) {
        let x = y.left;
        let T2 = x.right;

        x.right = y;
        y.left = T2;

        y.height = Math.max(this.getHeight(y.left), this.getHeight(y.right)) + 1;
        x.height = Math.max(this.getHeight(x.left), this.getHeight(x.right)) + 1;

        return x;
    }

    leftRotate(x) {
        let y = x.right;
        let T2 = y.left;

        y.left = x;
        x.right = T2;

        x.height = Math.max(this.getHeight(x.left), this.getHeight(x.right)) + 1;
        y.height = Math.max(this.getHeight(y.left), this.getHeight(y.right)) + 1;

        return y;
    }

    insert(node, value) {
        if (node === null) return new Node(value);

        if (value < node.value) {
            node.left = this.insert(node.left, value);
        } else if (value > node.value) {
            node.right = this.insert(node.right, value);
        } else {
            return node;
        }

        node.height = 1 + Math.max(this.getHeight(node.left), this.getHeight(node.right));

        let balance = this.getBalanceFactor(node);

        if (balance > 1 && value < node.left.value) {
            return this.rightRotate(node);
        }

        if (balance < -1 && value > node.right.value) {
            return this.leftRotate(node);
        }

        if (balance > 1 && value > node.left.value) {
            node.left = this.leftRotate(node.left);
            return this.rightRotate(node);
        }

        if (balance < -1 && value < node.right.value) {
            node.right = this.rightRotate(node.right);
            return this.leftRotate(node);
        }

        return node;
    }

    display(node, space = 0) {
        if (node === null) return;
        space += 10;

        this.display(node.right, space);
        console.log();
        for (let i = 10; i < space; i++) {
            process.stdout.write(" ");
        }
        console.log(node.value);

        this.display(node.left, space);
    }
}

const avlTree = new AVL();

function printMenu() {
    console.log("\n\tMenu de Opções\n");
    console.log("1. Inicializa a árvore");
    console.log("2. Insere na árvore");
    console.log("3. Buscar um valor na árvore");
    console.log("4. Conta o número de nós da árvore");
    console.log("5. Imprime a árvore");
    console.log("6. Remove um nó da árvore");
    console.log("0. Sair");
}

function initializeTree() {
    avlTree.root = null;
    console.log("Árvore inicializada com sucesso.");
}

function insertValue() {
    rl.question("Digite um número para inserir na árvore: ", (value) => {
        avlTree.root = avlTree.insert(avlTree.root, parseInt(value));
        console.log("Nó inserido com sucesso.");
        menu();
    });
}

function searchValue() {
    rl.question("Digite um valor para pesquisar na árvore: ", (value) => {
        if (avlTree.search(parseInt(value))) {
            console.log(`O valor ${value} foi encontrado na árvore.`);
        } else {
            console.log(`O valor ${value} não foi encontrado na árvore.`);
        }
        menu();
    });
}

function countNodes() {
    console.log(`A árvore possui ${avlTree.countNodes()} nós.`);
    menu();
}

function removeNode() {
    rl.question("Digite um valor para remover da árvore: ", (value) => {
        avlTree.root = avlTree.remove(avlTree.root, parseInt(value));
        console.log("Valor removido com sucesso.");
        menu();
    });
}

function menu() {
    printMenu();
    rl.question("Escolha uma opção: ", (option) => {
        switch (option) {
            case '1':
                initializeTree();
                break;
            case '2':
                insertValue();
                break;
            case '3':
                searchValue();
                break;
            case '4':
                countNodes();
                break;
            case '5':
                console.log("Árvore AVL:");
                avlTree.display(avlTree.root);
                menu();
                break;
            case '6':
                removeNode();
                break;
            case '0':
                rl.close();
                break;
            default:
                console.log("Opção inválida. Por favor, escolha uma opção válida.");
                menu();
                break;
        }
    });
}

menu();
