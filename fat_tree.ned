
network FatTree {
	submodules:
		// Core layer
		core0: Node { @display("p=270.0,50"); }
		core1: Node { @display("p=350.0,50"); }
		core2: Node { @display("p=430.0,50"); }
		core3: Node { @display("p=510.0,50"); }
		// Pod 0
		aggr00: Node { @display("p=50.0,210"); }
		aggr01: Node { @display("p=130.0,210"); }
		edge00: Node { @display("p=50.0,290"); }
		edge01: Node { @display("p=130.0,290"); }
		// Pod 1
		aggr10: Node { @display("p=250.0,210"); }
		aggr11: Node { @display("p=330.0,210"); }
		edge10: Node { @display("p=250.0,290"); }
		edge11: Node { @display("p=330.0,290"); }
		// Pod 2
		aggr20: Node { @display("p=450.0,210"); }
		aggr21: Node { @display("p=530.0,210"); }
		edge20: Node { @display("p=450.0,290"); }
		edge21: Node { @display("p=530.0,290"); }
		// Pod 3
		aggr30: Node { @display("p=650.0,210"); }
		aggr31: Node { @display("p=730.0,210"); }
		edge30: Node { @display("p=650.0,290"); }
		edge31: Node { @display("p=730.0,290"); }
	connections:
		// Pod 0
		edge00.up++ <--> aggr00.down++;
		edge00.up++ <--> aggr01.down++;
		edge01.up++ <--> aggr00.down++;
		edge01.up++ <--> aggr01.down++;
		aggr00.up++ <--> core0.down++;
		aggr00.up++ <--> core1.down++;
		aggr00.up++ <--> core2.down++;
		aggr00.up++ <--> core3.down++;
		aggr01.up++ <--> core0.down++;
		aggr01.up++ <--> core1.down++;
		aggr01.up++ <--> core2.down++;
		aggr01.up++ <--> core3.down++;
		// Pod 1
		edge10.up++ <--> aggr10.down++;
		edge10.up++ <--> aggr11.down++;
		edge11.up++ <--> aggr10.down++;
		edge11.up++ <--> aggr11.down++;
		aggr10.up++ <--> core0.down++;
		aggr10.up++ <--> core1.down++;
		aggr10.up++ <--> core2.down++;
		aggr10.up++ <--> core3.down++;
		aggr11.up++ <--> core0.down++;
		aggr11.up++ <--> core1.down++;
		aggr11.up++ <--> core2.down++;
		aggr11.up++ <--> core3.down++;
		// Pod 2
		edge20.up++ <--> aggr20.down++;
		edge20.up++ <--> aggr21.down++;
		edge21.up++ <--> aggr20.down++;
		edge21.up++ <--> aggr21.down++;
		aggr20.up++ <--> core0.down++;
		aggr20.up++ <--> core1.down++;
		aggr20.up++ <--> core2.down++;
		aggr20.up++ <--> core3.down++;
		aggr21.up++ <--> core0.down++;
		aggr21.up++ <--> core1.down++;
		aggr21.up++ <--> core2.down++;
		aggr21.up++ <--> core3.down++;
		// Pod 3
		edge30.up++ <--> aggr30.down++;
		edge30.up++ <--> aggr31.down++;
		edge31.up++ <--> aggr30.down++;
		edge31.up++ <--> aggr31.down++;
		aggr30.up++ <--> core0.down++;
		aggr30.up++ <--> core1.down++;
		aggr30.up++ <--> core2.down++;
		aggr30.up++ <--> core3.down++;
		aggr31.up++ <--> core0.down++;
		aggr31.up++ <--> core1.down++;
		aggr31.up++ <--> core2.down++;
		aggr31.up++ <--> core3.down++;
}
