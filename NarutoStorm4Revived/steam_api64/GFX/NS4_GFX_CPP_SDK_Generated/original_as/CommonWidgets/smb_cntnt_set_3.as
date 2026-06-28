package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol35")]
   public dynamic class smb_cntnt_set_3 extends MovieClip
   {
      
      public var mc_base1:nut_base;
      
      public var txt_cntnt00:smb_font;
      
      public var txt_head00:smb_font;
      
      public function smb_cntnt_set_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_head00.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_cntnt00.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_cntnt00.SetTextSize(30);
         this.txt_cntnt00.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_cntnt00.SetTextFieldWidth(1300);
         this.txt_cntnt00.SetTextFit(true);
      }
   }
}

