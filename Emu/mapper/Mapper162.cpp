//////////////////////////////////////////////////////////////////////////
// Mapper162	WaiXing FS304/FS301_1                                   //
//////////////////////////////////////////////////////////////////////////

void	Mapper162::Reset()
{
	reg5000 = 3;
	reg5100 = 0;
	reg5200 = 0;
	reg5300 = 7;
	SetBank_CPU();
	SetBank_PPU();
}

void Mapper162::WriteLow(WORD addr, BYTE data)
{
//	DEBUGOUT("Address=%04X Data=%02X\n", addr&0xFFFF, data&0xFF );

	if(addr==0x5000){
		reg5000 = data;
		SetBank_CPU();
		SetBank_PPU();
	}else if(addr==0x5100){
		reg5100 = data;
		SetBank_CPU();
		SetBank_PPU();
	}else if(addr==0x5200){
		reg5200 = data;
		SetBank_CPU();
		SetBank_PPU();
	}else if(addr==0x5300){
		reg5300 = data;
	}else if(addr>=0x6000){
		CPU_MEM_BANK[addr>>13][addr&0x1FFF] = data;
	}else{
		DEBUGOUT("write to %04x:%02x\n", addr, data);
	}
}

void Mapper162::Write(WORD addr, BYTE data)
{

	DEBUGOUT("Address=%04X Data=%02X\n", addr&0xFFFF, data&0xFF );

}

void	Mapper162::SetBank_CPU()
{
	BYTE bank;
	switch (reg5300)
	{
		case 4:
			bank = (((reg5000 & 0xF) + ((reg5100 & 3) >> 1) ) | ((reg5200 & 3) << 4));
			break;
		case 7:
			bank = (((reg5000 & 0xF) + ((reg5100 & 1) << 4) ) | ((reg5200 & 3) << 4));
//			bank = ((reg5000 & 0xF) | ((reg5200 & 1) << 4));
			break;
	}
	SetPROM_32K_Bank(bank);
}

void	Mapper162::SetBank_PPU()
{
	SetCRAM_8K_Bank(0);
}

void	Mapper162::HSync(int scanline)
{
	if( (reg5000&0x80) && nes->ppu->IsDispON() ) {
		if(scanline<127){
			SetCRAM_4K_Bank(4, 0);
		}else if(scanline<240){
			SetCRAM_4K_Bank(4, 1);
		}
	}
}