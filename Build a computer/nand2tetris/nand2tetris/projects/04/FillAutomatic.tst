load Fill.hack,
output-file FillAutomatic.out,
compare-to FillAutomatic.cmp,
output-list RAM[16384]%D2.6.2 RAM[17648]%D2.6.2 RAM[18349]%D2.6.2 RAM[19444]%D2.6.2 RAM[20771]%D2.6.2 RAM[21031]%D2.6.2 RAM[22596]%D2.6.2 RAM[23754]%D2.6.2 RAM[24575]%D2.6.2;

set RAM[24576] 0,
repeat 1000000 {
  ticktock;
}
output;

set RAM[24576] 1,
repeat 1000000 {
  ticktock;
}
output;

set RAM[24576] 0,
repeat 1000000 {
  ticktock;
}
output;

