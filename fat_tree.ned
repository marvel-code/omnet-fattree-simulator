network FatTree {
	submodules:
		// SDN controller
		controller: Controller { @display("p=390.0,50"); }
		// Core layer
		core0: Node { @display("p=270.0,290"); }
		core1: Node { @display("p=350.0,290"); }
		core2: Node { @display("p=430.0,290"); }
		core3: Node { @display("p=510.0,290"); }
		// Pod 0
		aggr00: Node { @display("p=50.0,370"); }
		aggr01: Node { @display("p=130.0,370"); }
		edge00: Node { @display("p=50.0,450"); }
		edge01: Node { @display("p=130.0,450"); }
		// Pod 1
		aggr10: Node { @display("p=250.0,370"); }
		aggr11: Node { @display("p=330.0,370"); }
		edge10: Node { @display("p=250.0,450"); }
		edge11: Node { @display("p=330.0,450"); }
		// Pod 2
		aggr20: Node { @display("p=450.0,370"); }
		aggr21: Node { @display("p=530.0,370"); }
		edge20: Node { @display("p=450.0,450"); }
		edge21: Node { @display("p=530.0,450"); }
		// Pod 3
		aggr30: Node { @display("p=650.0,370"); }
		aggr31: Node { @display("p=730.0,370"); }
		edge30: Node { @display("p=650.0,450"); }
		edge31: Node { @display("p=730.0,450"); }
	connections:
		// Pod 0
		edge00.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr00.down++;
		edge00.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr01.down++;
		edge01.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr00.down++;
		edge01.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr01.down++;
		aggr00.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr00.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr00.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr00.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		aggr01.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr01.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr01.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr01.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		// Pod 1
		edge10.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr10.down++;
		edge10.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr11.down++;
		edge11.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr10.down++;
		edge11.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr11.down++;
		aggr10.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr10.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr10.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr10.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		aggr11.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr11.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr11.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr11.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		// Pod 2
		edge20.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr20.down++;
		edge20.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr21.down++;
		edge21.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr20.down++;
		edge21.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr21.down++;
		aggr20.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr20.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr20.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr20.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		aggr21.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr21.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr21.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr21.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		// Pod 3
		edge30.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr30.down++;
		edge30.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr31.down++;
		edge31.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr30.down++;
		edge31.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> aggr31.down++;
		aggr30.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr30.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr30.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr30.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		aggr31.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core0.down++;
		aggr31.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core1.down++;
		aggr31.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core2.down++;
		aggr31.up++ <--> {delay=0ms; datarate=100.0Mbps;} <--> core3.down++;
		// Controller connections
		edge00.controller <--> controller.down++;
		edge01.controller <--> controller.down++;
		edge10.controller <--> controller.down++;
		edge11.controller <--> controller.down++;
		edge20.controller <--> controller.down++;
		edge21.controller <--> controller.down++;
		edge30.controller <--> controller.down++;
		edge31.controller <--> controller.down++;
		aggr00.controller <--> controller.down++;
		aggr01.controller <--> controller.down++;
		aggr10.controller <--> controller.down++;
		aggr11.controller <--> controller.down++;
		aggr20.controller <--> controller.down++;
		aggr21.controller <--> controller.down++;
		aggr30.controller <--> controller.down++;
		aggr31.controller <--> controller.down++;
		core0.controller <--> controller.down++;
		core1.controller <--> controller.down++;
		core2.controller <--> controller.down++;
		core3.controller <--> controller.down++;
}
