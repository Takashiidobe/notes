package lexer

type Lexer struct {
	input        string
	position     int
	readPosition int
}

func New(input string) *Lexer {
	l := &Lexer{input: input}
	return l
}
