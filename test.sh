#!/bin/bash
echo "MOUNTING FILE SYSTEM"
./myfs tmp
directory="tmp/test_directory"
echo "Making directory $directory"
mkdir $directory
sleep 1
echo "UNMOUNTING FILE SYSTEM"
fusermount -u tmp

echo "MOUNTING FILE SYSTEM"
./myfs tmp
if [ -d $directory ]; then
    echo "SUCCESS: Directory was created."
else
    echo "ERROR: Directory does not exist."
fi #конец сравнения

i=0
while [ $i -lt 10 ]
do
  addr="$directory/file$i.htm"
  touch $addr #создаем пустой файл
  cp FUSE.htm $addr #копируем
  echo "File $addr was created." 
  i=$(( $i + 1 )) 
done
sleep 1
echo "UNMOUNTING FILE SYSTEM"
fusermount -u tmp

echo "MOUNTING FILE SYSTEM"
./myfs tmp
echo "Checking files:"
i=0
while [ $i -lt 10 ]
do
  addr="$directory/file$i.htm"
  echo "Checking $addr:"
  if ((diff FUSE.htm $addr) &> /dev/null) && ((diff $addr FUSE.htm) &> /dev/null); then
    echo "OK"
  else
    echo "FAIL"
  fi
diff FUSE.htm $addr #получение разницы между файлами
diff $addr FUSE.htm
  i=$(( $i + 1 ))
done

echo "Removing directory $directory"
rmdir $directory
sleep 1
echo "UNMOUNTING FILE SYSTEM"
fusermount -u tmp

echo "MOUNTING FILE SYSTEM"
./myfs tmp
# проверяем удаление директории
if [ -d $directory ]; then
    echo "ERROR: Directory still exists."
else
    echo "SUCCESS: Directory was removed."
fi
echo "UNMOUNTING FILE SYSTEM"
sleep 1
fusermount -u tmp
