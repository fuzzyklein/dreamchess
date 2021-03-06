/*  DreamChess
**
**  DreamChess is the legal property of its developers, whose names are too
**  numerous to list here. Please refer to the AUTHORS.txt file distributed
**  with this source distribution.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DREAMER_BOARD_H
#define DREAMER_BOARD_H

/* Chess pieces. Also used for indexing the bitboard array. */
#define PAWN 0
#define WHITE_PAWN 0
#define BLACK_PAWN 1
#define KNIGHT 2
#define WHITE_KNIGHT 2
#define BLACK_KNIGHT 3
#define BISHOP 4
#define WHITE_BISHOP 4
#define BLACK_BISHOP 5
#define ROOK 6
#define WHITE_ROOK 6
#define BLACK_ROOK 7
#define QUEEN 8
#define WHITE_QUEEN 8
#define BLACK_QUEEN 9
#define KING 10
#define WHITE_KING 10
#define BLACK_KING 11
#define ALL 12
#define WHITE_ALL 12
#define BLACK_ALL 13

#define SQUARE_BIT(A) (1LL << (A))

/* Empty squares required for kingside castle. */
#define WHITE_EMPTY_KINGSIDE (SQUARE_BIT(SQUARE_F1) | SQUARE_BIT(SQUARE_G1))
#define BLACK_EMPTY_KINGSIDE (SQUARE_BIT(SQUARE_F8) | SQUARE_BIT(SQUARE_G8))

/* Empty squares required for queenside castle. */
#define WHITE_EMPTY_QUEENSIDE (SQUARE_BIT(SQUARE_B1) | SQUARE_BIT(SQUARE_C1) | SQUARE_BIT(SQUARE_D1))
#define BLACK_EMPTY_QUEENSIDE (SQUARE_BIT(SQUARE_B8) | SQUARE_BIT(SQUARE_C8) | SQUARE_BIT(SQUARE_D8))

/* Squares where phantom kings are placed during a kingside castle to detect an
** illegal move.
*/
#define WHITE_PHANTOM_KINGSIDE (SQUARE_BIT(SQUARE_E1) | SQUARE_BIT(SQUARE_F1))
#define BLACK_PHANTOM_KINGSIDE (SQUARE_BIT(SQUARE_E8) | SQUARE_BIT(SQUARE_F8))

/* Squares where phantom kings are placed during a queenside castle to detect an
** illegal move.
*/
#define WHITE_PHANTOM_QUEENSIDE (SQUARE_BIT(SQUARE_E1) | SQUARE_BIT(SQUARE_D1))
#define BLACK_PHANTOM_QUEENSIDE (SQUARE_BIT(SQUARE_E8) | SQUARE_BIT(SQUARE_D8))

/* Sides.*/
#define SIDE_WHITE 0
#define SIDE_BLACK 1
#define OPPONENT(P) (((P) + 1) % 2) /*(P % 1) */

/* Chess piece mask. */
#define PIECE_MASK 14
#define PIECE_IS_WHITE(A) (!((A)&1)) /* A % 1 */
#define PIECE_IS_BLACK(A) ((A)&1)

/* Castling. */

#define CASTLE_KINGSIDE 0
#define CASTLE_QUEENSIDE 2

#define WHITE_CAN_CASTLE_KINGSIDE (1 << 0)
#define BLACK_CAN_CASTLE_KINGSIDE (1 << 1)
#define WHITE_CAN_CASTLE_QUEENSIDE (1 << 2)
#define BLACK_CAN_CASTLE_QUEENSIDE (1 << 3)
#define WHITE_HAS_CASTLED (1 << 4)
#define BLACK_HAS_CASTLED (1 << 5)
#define WHITE_PHANTOM_KINGS_KINGSIDE (1 << 6)
#define WHITE_PHANTOM_KINGS_QUEENSIDE (1 << 7)
#define BLACK_PHANTOM_KINGS_KINGSIDE (1 << 8)
#define BLACK_PHANTOM_KINGS_QUEENSIDE (1 << 9)

#define PHANTOM_FLAGS (15 << 6)

/* Squares on the board. */
#define SQUARE_A1 0
#define SQUARE_B1 1
#define SQUARE_C1 2
#define SQUARE_D1 3
#define SQUARE_E1 4
#define SQUARE_F1 5
#define SQUARE_G1 6
#define SQUARE_H1 7
#define SQUARE_A2 8
#define SQUARE_B2 9
#define SQUARE_C2 10
#define SQUARE_D2 11
#define SQUARE_E2 12
#define SQUARE_F2 13
#define SQUARE_G2 14
#define SQUARE_H2 15
#define SQUARE_A3 16
#define SQUARE_B3 17
#define SQUARE_C3 18
#define SQUARE_D3 19
#define SQUARE_E3 20
#define SQUARE_F3 21
#define SQUARE_G3 22
#define SQUARE_H3 23
#define SQUARE_A4 24
#define SQUARE_B4 25
#define SQUARE_C4 26
#define SQUARE_D4 27
#define SQUARE_E4 28
#define SQUARE_F4 29
#define SQUARE_G4 30
#define SQUARE_H4 31
#define SQUARE_A5 32
#define SQUARE_B5 33
#define SQUARE_C5 34
#define SQUARE_D5 35
#define SQUARE_E5 36
#define SQUARE_F5 37
#define SQUARE_G5 38
#define SQUARE_H5 39
#define SQUARE_A6 40
#define SQUARE_B6 41
#define SQUARE_C6 42
#define SQUARE_D6 43
#define SQUARE_E6 44
#define SQUARE_F6 45
#define SQUARE_G6 46
#define SQUARE_H6 47
#define SQUARE_A7 48
#define SQUARE_B7 49
#define SQUARE_C7 50
#define SQUARE_D7 51
#define SQUARE_E7 52
#define SQUARE_F7 53
#define SQUARE_G7 54
#define SQUARE_H7 55
#define SQUARE_A8 56
#define SQUARE_B8 57
#define SQUARE_C8 58
#define SQUARE_D8 59
#define SQUARE_E8 60
#define SQUARE_F8 61
#define SQUARE_G8 62
#define SQUARE_H8 63

/* Total number of types of pieces. */
#define NR_PIECES 12

/* Total number of bitboards. */
#define NR_BITBOARDS 14

/* Empty square. */
#define NONE 12

/* 64-bit bitboard. Bit 0 = A1, bit 1 = A2 etc. */
typedef unsigned long long bitboard_t;

class Move {
private:
	enum TypeBit { RegularBit = 16, CaptureBit = 8, PromotionBit = 4 };

public:
	enum class Type : unsigned char {
		None = 0,
		Resign = 1,
		Stalemate = 2,
		Normal = RegularBit,
		Capture = RegularBit | CaptureBit,
		Promotion = RegularBit | PromotionBit,
		PromotionCapture = RegularBit | PromotionBit | CaptureBit,
		KingsideCastle = RegularBit | 1,
		QueensideCastle = RegularBit | 2,
		EnPassant = RegularBit | CaptureBit | 3,
	};

	Move();
	Move(unsigned int piece, unsigned int source, unsigned int dest, Type type, unsigned int captured);

	bool operator==(Move &rhs) const;

	unsigned int getPiece() const;
	unsigned int getPieceKind() const;
	unsigned int getPieceColour() const;
	unsigned int getSource() const;
	unsigned int getDest() const;
	Type getType() const;
	unsigned int getCapturedPiece() const;
	bool doesCapture() const;
	bool doesPromotion() const;
	bool isRegular() const;
	bool isNone() const;

private:
	Type _type;
	unsigned char _source;
	unsigned char _dest;
	unsigned char _piece : 4;
	unsigned char _captured : 4;
};

class Board {
public:
	/* Looks for a piece on the board at a specified location.
	** Parameters: (board_t *) board: Pointer to the board to search.
	**             (int) square: The square to search.
	** Returns   : (int): The black piece located at the square on the board, or
	**                 NONE if no black piece was found. If both a fake king
	**                 and a rook are on the square, the king is found instead
	**                 of the rook.
	*/
	template <int SIDE> int findPiece(int square) const;

	/* Clears a board.
	** Parameters: (board_t *) board: Pointer to the board to clear.
	** Returns   : (void)
	*/
	void clear();

	/* Sets up a board to the starting position.
	** Parameters: (board_t *) board: Pointer to the board to set up.
	** Returns   : (void)
	*/
	void setup();

	/* Makes a move on a board.
	** Parameters: (board_t *) board: Board to make the move on.
	**             (Move) move: The move to make.
	** Returns   : (void)
	*/
	void makeMove(Move move);

	/* Unmakes a move on a board.
	** Parameters: (board_t *) board: Board to unmake the move on.
	**             (Move) move: The move to unmake.
	**             (bitboard_t) old_en_passant: The en-passant flags before the
	**                 last move.
	**             (int) old_castle_flags: The castling flags before the last
	**                 move.
	**             (int) old_fifty_moves: The 50 moves value before the last
	**                 move.
	** Returns   : (void)
	*/
	void unmakeMove(Move move, bitboard_t old_en_passant, int old_castle_flags, int old_fifty_moves);

	bool setupFEN(const char *fen);

	bitboard_t bitboard[NR_BITBOARDS];

	/* Hash key of the current board. */
	long long hash_key;

	/* 0-3 can_castle flags
	** 4-5 has_castled flags
	** 6-9 phantom kings flags
	*/
	int castle_flags;

	/* bitboard containing the current en_passant flags, if any. */
	bitboard_t en_passant;

	/* Current player. 0 = white, 1 = black. */
	int current_player;

	/* Current total material value for both black and white. */
	int material_value[2];

	/* Number of pawns on the board for both black and white. */
	int num_pawns[2];

	/* 50-move counter. */
	int fifty_moves;

private:
	void addPiece(int square, int piece);
	void removePiece(int square, int piece);
};

extern bitboard_t square_bit[64];

template <int SIDE> int Board::findPiece(int square) const {
	bitboard_t mask = square_bit[square];

	/* We need to check kings first because a fake king might be on the
	** same square as a rook. In that case we want to find the king so
	** that the illegality of the previous move can be detected.
	*/
	if (bitboard[KING + SIDE] & square_bit[square])
		return KING + SIDE;

	/* Check for other pieces in order of frequency. */
	if (bitboard[PAWN + SIDE] & mask)
		return PAWN + SIDE;
	if (bitboard[KNIGHT + SIDE] & mask)
		return KNIGHT + SIDE;
	if (bitboard[BISHOP + SIDE] & mask)
		return BISHOP + SIDE;
	if (bitboard[ROOK + SIDE] & mask)
		return ROOK + SIDE;
	if (bitboard[QUEEN + SIDE] & mask)
		return QUEEN + SIDE;

	return NONE;
}

void board_init(void);
/* Initialises the global array square_bit.
** Parameters: (void)
** Returns   : (void)
*/

#endif
