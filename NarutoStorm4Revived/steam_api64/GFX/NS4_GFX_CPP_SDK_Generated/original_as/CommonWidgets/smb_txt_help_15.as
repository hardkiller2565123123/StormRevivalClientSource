package shop_cmn_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class smb_txt_help_15 extends MovieClip
   {
      
      public var txt_help:smb_font;
      
      public function smb_txt_help_15()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_help.SetTextSize(29);
         this.txt_help.SetTextColor(0);
         this.txt_help.SetTextFieldWidth(1400);
         this.txt_help.SetTextWordWrap(true);
         this.txt_help.SetTextStandardAlignByLanguage();
         this.txt_help.SetTextPivot(smb_font.CCD_PIVOT_LC);
      }
   }
}

