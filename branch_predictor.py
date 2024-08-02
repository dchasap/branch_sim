
"""
__name__ = branch_predictor.py
__author__ = Dimitrios Chasapis 
__description = Implements a Python interaface for branch predictors (that may be implemented in CPP)
                to be used by naive_sim.py
"""

from ctypes import cdll
from ctypes import c_void_p
lgshare = cdll.LoadLibrary('./libgshare.so')
lhashed_perceptron = cdll.LoadLibrary('./libhashed_perceptron.so')
ltage_sc_l= cdll.LoadLibrary('./libtage_sc_l.so')

class GShare(object):
    
    def __init__(self):
        _cpp_ptr_wrapper = lgshare.create_GShare
        _cpp_ptr_wrapper.restype = c_void_p
        self.obj = c_void_p(_cpp_ptr_wrapper())

    def init(self):
        lgshare.initialize_GShare(self.obj)

    def predict(self, ip):
        return lgshare.predict_GShare(self.obj, ip)

    def update(self, ip, branch_type, taken, prediction, target):
        lgshare.update_GShare(self.obj, ip, branch_type, taken, prediction, target)

class HashedPerceptron(object):
    
    def __init__(self):
        _cpp_ptr_wrapper = lhashed_perceptron.create_HashedPerceptron
        _cpp_ptr_wrapper.restype = c_void_p
        self.obj = c_void_p(_cpp_ptr_wrapper())

    def init(self):
        lhashed_perceptron.initialize_HashedPerceptron(self.obj)

    def predict(self, ip):
        return lhashed_perceptron.predict_HashedPerceptron(self.obj, ip)

    def update(self, ip, branch_type, taken, prediction, target):
        lhashed_perceptron.update_HashedPerceptron(self.obj, ip, branch_type, taken, prediction, target)

class TAGE_SC_L(object):
    
    def __init__(self):
        _cpp_ptr_wrapper = ltage_sc_l.create_TAGE_SC_L
        _cpp_ptr_wrapper.restype = c_void_p
        self.obj = c_void_p(_cpp_ptr_wrapper())

    def init(self):
        ltage_sc_l.initialize_TAGE_SC_L(self.obj)

    def predict(self, ip):
        return ltage_sc_l.predict_TAGE_SC_L(self.obj, ip)

    def update(self, ip, branch_type, taken, prediction, target):
        print(branch_type)
        #ltage_sc_l.update_TAGE_SC_L(self.obj, ip, branch_type, taken, prediction, target)


def create_branch_predictor(bpred_name):
    if (bpred_name == "gshare"):
        bpred = GShare()
    elif (bpred_name == "hashed_perceptron"):
        bpred = HashedPerceptron()
    elif (bpred_name == "tage_sc_l"):
        bpred = TAGE_SC_L()
    else:
        print(bpred_name + " is not a supported branch predictor.")

    bpred.init()
    return bpred

