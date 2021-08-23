import numpy as np
import sys
import logging
from ModulationPy.ModulationPy import QAMModem, PSKModem
np.set_printoptions(threshold=np.inf)

class TestThing():
  def PskModulate(self,msg,max_num):
    msg = list(map(int, num_list))
    """ PSK modem  modulation and demodulation tests"""
    msg = np.array(msg)
    # Hard decision, Gray mapping, non-binary IO
    Modem = PSKModem(max_num, gray_map=True, bin_input=False, soft_decision = False, bin_output = False)  
    return Modem.modulate(msg)
    # np.testing.assert_array_equal(msg, Modem.demodulate(Modem.modulate(msg)))

    # Hard decision, binary mapping, non-binary IO
    # Modem = PSKModem(M, gray_map=False, bin_input=False, soft_decision = False, bin_output = False)
    # print(Modem.modulate(msg))
    # np.testing.assert_array_equal(msg, Modem.demodulate(Modem.modulate(msg)))

  def PskDeModulate(self,msg,max_num):
    """ PSK modem  modulation and demodulation tests"""
    msg = list(map(float, num_list))
    leng = len(msg)//2;
    tmp = np.empty(leng,dtype=complex)
    for i in range(leng):
      tmp[i] = msg[2*i] + msg[2*i+1]*1j
    logging.info('%s' % str(tmp))
    # Hard decision, Gray mapping, non-binary IO
    msg = tmp
    Modem = PSKModem(max_num, gray_map=True, bin_input=False, soft_decision = False, bin_output = False)  
    return Modem.demodulate(msg)

if __name__ == '__main__':
  # argv[1] = method  argv[2] = max_num  argv[3:] = ar
  num_list = sys.argv[3:]
  max_num = int(sys.argv[2])
  test = TestThing()
  if sys.argv[1] == 'modulate':
    ar = test.PskModulate(num_list,max_num)
    for c in ar:
      print(str(c.real) + " " + str(c.imag))
  else:
    ar = test.PskDeModulate(num_list,max_num)
    for c in ar:
      print(c)
