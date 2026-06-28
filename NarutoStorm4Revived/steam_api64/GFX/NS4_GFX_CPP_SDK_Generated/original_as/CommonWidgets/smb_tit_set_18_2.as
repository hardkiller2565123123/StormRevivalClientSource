package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.icon_new.nut_new;
   import script.xcmn_font.smb_font;
   import script.xcp_frame1.smb_xcp_frame1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public dynamic class smb_tit_set_18 extends MovieClip
   {
      
      public var mc_base2:smb_xcp_frame1;
      
      public var mc_new:nut_new;
      
      public var txt_bns:smb_font;
      
      public var txt_bns_num:smb_font;
      
      public var txt_bns_tit02:smb_font;
      
      public function smb_tit_set_18()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_bns_tit02.SetTextColor(16773768);
         this.txt_bns_tit02.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_bns_tit02.SetTextSize(28);
         this.txt_bns_tit02.SetTextFieldWidth(1075);
         this.txt_bns_tit02.SetTextFit(true);
         this.txt_bns_num.SetTextColor(16773768);
         this.txt_bns_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_bns_num.SetTextSize(30);
         this.txt_bns_num.SetTextFieldWidth(100);
         this.txt_bns_num.SetTextFit(true);
         this.txt_bns.SetTextColor(16773768);
         this.txt_bns.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_bns.SetTextSize(30);
         this.txt_bns.SetTextFieldWidth(960);
         this.txt_bns.SetTextFit(true);
      }
   }
}

