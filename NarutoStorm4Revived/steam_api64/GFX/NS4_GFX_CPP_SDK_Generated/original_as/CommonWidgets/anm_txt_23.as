package cutin_msion_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class anm_txt_23 extends MovieClip
   {
      
      public var txt_info:smb_font;
      
      public function anm_txt_23()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_info.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_info.SetTextSize(100);
         this.txt_info.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_info.SetTextFit(true);
         this.txt_info.SetTextFieldWidth(1520);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_info.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_info.SetTextSize(70);
         this.txt_info.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_info.SetTextFit(true);
         this.txt_info.SetTextFieldWidth(1520);
      }
   }
}

