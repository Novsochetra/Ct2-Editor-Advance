//////////////////////////////////////////////////////////////////////////
// Mapper176         ShuQiYu / HengGe / WaiXing                         //
//////////////////////////////////////////////////////////////////////////
void	Mapper176::Reset()
{
	if(PROM_16K_SIZE>32){
		SetPROM_32K_Bank( 0, 1, (PROM_8K_SIZE/2)-2, (PROM_8K_SIZE/2)-1 );	//For 1M byte Cartridge
	}else{
		SetPROM_32K_Bank( 0, 1, PROM_8K_SIZE-2, PROM_8K_SIZE-1 );
	}
	if(VROM_1K_SIZE) SetVROM_8K_Bank( 0 );
	reg5000 = 0;
	reg5001 = 0;
	reg5010 = 0;
	reg5011 = 0;
	reg5013 = 0;
	reg5FF1 = 0;
	reg5FF2 = 0;
	we_sram  = 0;
	SBW = 0;
/*
	crc == 0x416C07A1		//[ES-1006] Meng Huan Zhi Xing IV (C) & WXN-梦幻之星	√
	crc == 0x94782FBD		//[ES-1057] San Guo Zhi - Xiong Ba Tian Xia (C)
	crc == 0xF9863ADF		//[ES-1066] Xi Chu Ba Wang (C)
	crc == 0xB511C04B		//[ES-1071] San Xia Wu Yi (C)
	crc == 0x1923A8C5		//[ES-1087] Shui Hu Shen Shou (C) & WXN-水浒神兽(fix)	√
	crc == 0x095D8678		//[ES-0122] Shuang Yue Zhuan (C) --> fecumm-mapper176
	crc == 0x7696573A		//[ES-0122] Ya Te Lu Zhan Ji (C) --> fecumm-mapper176
	crc == 0x8f6ab5ac		//WXN-三国忠烈传		√
	crc == 0x99051cb5		//WXN-雄霸天下			√
	crc == 0xf29c8186		//WXN-大富翁2-上海大亨	√
	crc == 0xc768098b		//WXN-三侠五义			√
	crc == 0x49f22159		//WXN-超级大富翁		√
	crc == 0xf354d847		//WXN-格兰帝亚			√
	crc == 0x5ee2ef97		//WXN-帝国时代(fix)		√
	crc == 0x977d22c3		//WXN-破釜沉舟(fix)		√
	crc == 0xf1d803f3		//WXN-西楚霸王(fix)		√
	crc == 0x85dd49b6		//WXN-口袋金(fix)		√
	crc == 0x97b82f53		//WXN-爆笑三国(fix)		√
	crc == 0xce2ea530		//WXN-宠物翡翠(fix)		√
*/
}

void	Mapper176::WriteLow( WORD addr, BYTE data )
{
//	DEBUGOUT("Address=%04X Data=%02X\n", addr&0xFFFF, data&0xFF );

	switch( addr ) {
		case	0x5000:
			reg5000 = data;
			break;
		case	0x5001:			//[ES-1006] Meng Huan Zhi Xing IV (C)
			reg5001 = data;
			if(SBW) SetPROM_32K_Bank(reg5001);
			break;
		case	0x5010:
			reg5010 = data;
			if(reg5010==0x24) SBW=1;
			break;
		case	0x5011:
			reg5011 = data>>1;
			if(SBW)	SetPROM_32K_Bank(reg5011);
			break;
		case	0x5013:
			reg5013 = data;
			break;
		case	0x5ff1:
			reg5FF1 = data>>1;
			SetPROM_32K_Bank(reg5FF1);
			break;
		case	0x5ff2:
			reg5FF2 = data;
			SetVROM_8K_Bank(reg5FF2);
			break;
		}

	if( addr >= 0x6000 ) {
//		if ( we_sram == 0 ){
			CPU_MEM_BANK[addr>>13][addr&0x1FFF] = data;
//		}
	}

}

void	Mapper176::Write( WORD addr, BYTE data )
{
//	DEBUGOUT("Address=%04X Data=%02X\n", addr&0xFFFF, data&0xFF );

	if(addr==0xa000){
		data &= 0x03;
		if		( data == 0 )	SetVRAM_Mirror( VRAM_VMIRROR );
		else if	( data == 1 )	SetVRAM_Mirror( VRAM_HMIRROR );
		else if	( data == 2 )	SetVRAM_Mirror( VRAM_MIRROR4L );
		else					SetVRAM_Mirror( VRAM_MIRROR4H );
	}
	if(addr==0xa001){
		we_sram = data & 0x03;
	}
}
