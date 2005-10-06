// Siconos version 1.0, Copyright INRIA 2005.  
// Siconos is a program dedicated to modeling, simulation and control
// of non smooth dynamical systems.	
// Siconos is a free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// Siconos is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Siconos; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Contact: Vincent ACARY vincent.acary@inrialpes.fr 
//	
//
// getf("./siconos.sci");
//

//
//
// configure may generate paths :
//   for standard lib 
//   for siconos and numerics lib
//

function sicLink()
	// dynamic lib
        // FC core 3
        link("/usr/lib/libstdc++.so.6");
	link("/usr/lib/libdl.so");
	// xml
	link("/usr/lib/libxml2.so");
	// lapack++
	link("/usr/lib/liblapack.so");
	//link("/usr/local/lib/liblamatrix++.so");
	//link("/usr/local/lib/libblas++.so");
	link("/usr/local/lib/liblapack++.so");
	// Numerics and Siconos
	link("/local_home/pissard/Workspace/siconos/trunk/Numerics/lib/libNumerics.so");
	link("/local_home/pissard/Workspace/siconos-user/lib/libSiconosKernel.so");
	link("/local_home/pissard/Workspace/siconos/trunk/Front-End/scilab/siconos.so",['simul','sicLoadModel','sicTimeGetH','sicTimeGetK','sicTimeGetN','sicInitStrategy','sicSTNextStep','sicSTComputeFreeState','sicSTformalisePb','sicSTcomputePb','sicSTupdateState','sicModelgetQ'],'C');
endfunction


function [ret_val]=sicLoadModel(ModelXml)
        ret_val=call("sicLoadModel",ModelXml,2,"c","out",[1,1],1,"i");
endfunction

function [ret_val]=sicTimeGetH()
        ret_val=call("sicTimeGetH","out",[1,1],1,"d");
endfunction

function [ret_val]=sicTimeGetK()
        ret_val=call("sicTimeGetK","out",[1,1],1,"i");
endfunction

function [ret_val]=sicTimeGetN()
        ret_val=call("sicTimeGetN","out",[1,1],1,"i");
endfunction

function sicInitStrategy()
	call("sicInitStrategy");
endfunction

function sicSTNextStep()
	call("sicSTNextStep","out",[1,1],1,"i");
endfunction

function sicSTComputeFreeState()
	call("sicSTComputeFreeState","out",[1,1],1,"i");
endfunction

function sicSTformalisePb()
	call("sicSTformalisePb","out",[1,1],1,"i");
endfunction

function sicSTcomputePb()
	call("sicSTcomputePb","out",[1,1],1,"i");
endfunction

function sicSTupdateState()
	call("sicSTupdateState","out",[1,1],1,"i");
endfunction

function [ret_val]=sicModelgetQ(index)
	ret_val=call("sicModelgetQ",index,2,"i","out",[1,1],1,"d");
endfunction
