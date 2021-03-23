for i in *.json; do sed -i 's/\([a-z_:]*\)::dati/struct \1_dati/g' $i; done
for i in *.json; do sed -i 's/\([a-z_:]*\)::code/enum \1_code/g' $i; done
