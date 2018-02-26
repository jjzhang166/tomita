#encoding "utf-8"    // сообщаем парсеру о том, в какой кодировке написана грамматика
#GRAMMAR_ROOT S      // указываем корневой нетерминал грамматики


Pain -> 'боль' | 'болезненность';
Localization -> Prep Adj<gnc-agr[1]> Noun<gnc-agr[1]>;
S -> (Prep) Pain Localization;

//ProperName ->  Word<h-reg1>+;
//Person -> ProperName | 'человек';
//FormOfAddress -> 'товарищ' | 'мистер' | 'господин';
//AdjCoord -> Adj;
//AdjCoord -> AdjCoord<gnc-agr[1]> ',' Adj<gnc-agr[1]>;
//AdjCoord -> AdjCoord<gnc-agr[1]> 'и' Adj<gnc-agr[1]>;
//S -> Adj<gnc-agr[1]>+ (FormOfAddress) Person<gnc-agr[1], rt>;
//S -> AdjCoord<gnc-agr[1]> (FormOfAddress) Person<gnc-agr[1], rt>;