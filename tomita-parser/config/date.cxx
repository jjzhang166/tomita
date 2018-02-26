#encoding "utf-8"

Pain -> 'боль' | 'болезненность';
AdjPain -> (Adj<gnc-agr[1]>) Pain<gnc-agr[1], rt>;

Local -> Prep (Adj<gnc-agr[1]>) (Noun<gnc-agr[1]>) Noun<gnc-agr[1]>;
Local -> Prep (Noun<gnc-agr[1]>) Noun<gnc-agr[1]>;
Local -> Prep Noun<gnc-agr[1]> Noun<gnc-agr[1]> Noun<gnc-agr[1]>;

S -> (Prep) AdjPain interp (Pains.Pain) Local interp (Pains.Localization);

Commons -> Noun<kwtype="общиеСимптомы">;
Commons -> Noun Prep Commons;
S -> Commons interp (Pains.common);

