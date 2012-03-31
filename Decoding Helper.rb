keys = 'D','0','1','2','3','4','5','6','7','8','9','0','*','#','A','B','C'

def dec2bin(number)
   number = Integer(number);
   if(number == 0)
      return 0;
   end
   ret_bin = "";
   ## Untill val is zero, convert it into binary format
   while(number != 0)
      ret_bin = String(number % 2) + ret_bin;
      number = number / 2;
   end
   return ret_bin;
end

codes = 0b0000,
        0b0001,
        0b0010,
        0b0011,
        0b0100,
        0b0101,
        0b0110,
        0b0111,
        0b1000,
        0b1001,
        0b1010,
        0b1011,
        0b1100,
        0b1101,
        0b1110,
        0b1111

p keys
p result = codes.each { |code| p keys[code] }
p result == result

keys.each do |key|
  p dec2bin(key[0])
end
