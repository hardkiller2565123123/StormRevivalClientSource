package net_card_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol45")]
   public dynamic class txt_title01_27 extends MovieClip
   {
      
      public var txt_title00:smb_font;
      
      public var txt_title01:smb_font;
      
      public function txt_title01_27()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title00.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title00.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_title00.SetTextSize(28);
         this.txt_title00.SetTextFieldWidth(400);
         this.txt_title00.SetTextFit(true);
         this.txt_title01.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title01.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_title01.SetTextSize(28);
         this.txt_title01.SetTextFieldWidth(400);
         this.txt_title01.SetTextFit(true);
      }
   }
}

