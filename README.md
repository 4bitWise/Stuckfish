# Stuckfish

Stuckfish is a desktop application designed for reviewing chess games. Written in C++ with [Dear ImGui](https://github.com/ocornut/imgui), it offers a fast and free solution with an intuitive user interface for precise game analysis.

## **Installation**

Stuckfish will be directly available through releases. Simply download the latest release for your operating system and follow the installation instructions provided.

## **Features (Work in Progress)**

- [x] Fetch and display all games played this month via [Chess.com](http://chess.com/) API.
- [ ] Navigate to previous months' games with a "<" button.
- [ ] Load selected game onto the board by clicking on it.
- [ ] Receive notification when game analysis is complete.
- [ ] Adjust Stockfish analysis depth.
- [ ] Easily navigate moves with forward and backward buttons.
- [ ] Show opening moves by each player.
- [ ] Present game summary with precision details and winner indication.
- [ ] Provide move status (blunder, inaccuracy, miss, good, great, excellent, brilliant) feedback.
- [ ] Dockerize the application for simplified deployment.

## **Developer Resources**

For developers interested in contributing to Stuckfish, please refer to our [Developer Guide](https://github.com/4bitWise/stuckfish/blob/df5ee6ae88f429ead5d492ca5fafa7a81d9ea444/DEV_GUIDE.md) for detailed instructions.

## **Further Reading**

If you want to learn more about chess game analysis or even make your own, here are some recommended resources:

- [Stockfish](https://stockfishchess.org/): The powerful open-source chess engine used for analysis.
- **Stockfish API docs**: [StockfishOnline | Stockfish REST API](https://stockfish.online/docs.php)
- **Chess.com API docs**: [Published-Data API - Chess.com](https://www.chess.com/news/view/published-data-api)
- [Dear ImGui](https://github.com/ocornut/imgui): A bloat-free graphical user interface library for C++.
