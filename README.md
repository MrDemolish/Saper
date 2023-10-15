Opis ogólny
Projekt "Saper" to gra polegająca na odnajdywaniu min na planszy. Gra jest napisana w C++ z wykorzystaniem biblioteki SFML do grafiki i obsługi zdarzeń.

![380739112_1261963997801798_5811632103275220907_n](https://github.com/MrDemolish/Saper/assets/147986097/4f1b9a49-6de7-4a63-bc4f-1a1f00daa86f)

Wymagania
C++11 lub nowszy
Biblioteka SFML
System operacyjny zgodny z Windows (z powodu użycia funkcji Sleep())
Skopiować folder "res" do folderu kompilacji pliku .exe

Struktura kodu
Stałe i zmienne globalne
BOARD_SIZE: Rozmiar planszy.
CELL_SIZE: Rozmiar jednej komórki na planszy.
MINES: Liczba min na planszy.
MINE i EMPTY: Stałe do oznaczenia miny i pustej komórki.
board, revealed, flagged, questionMarked: Tablice przechowujące stan planszy i komórek.
font: Font używany w grze.
Prototypy funkcji
initializeBoard(): Inicjalizuje planszę.
reveal(int x, int y): Odkrywa komórki.
checkForGameEnd(sf::RenderWindow& window): Sprawdza, czy gra się zakończyła.
handleMouseClick(int x, int y, sf::Mouse::Button button): Obsługuje kliknięcia myszą.
Funkcje
initializeBoard()
Inicjalizuje planszę, umieszcza miny i liczby w komórkach.

reveal(int x, int y)
Odkrywa komórkę o podanych współrzędnych (x, y) i, jeśli jest pusta, odkrywa również jej sąsiadujące komórki.

checkForGameEnd(sf::RenderWindow& window)
Sprawdza, czy gracz wygrał lub przegrał, i odpowiednio zamyka okno gry.

handleMouseClick(int x, int y, sf::Mouse::Button button)
Obsługuje kliknięcia myszą, umożliwiając oznaczenie komórki flagą, znakiem zapytania lub odkrycie jej.

Główna pętla programu
Pętla główna programu zarządza grafiką i zdarzeniami. Rysuje planszę i elementy gry w oknie, a także obsługuje zdarzenia takie jak kliknięcia myszą.
