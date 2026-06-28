package net_rank_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class smb_txt_title_h_8 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function smb_txt_title_h_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(12305407);
         this.txt_title.SetTextFieldWidth(420);
         this.txt_title.SetTextFit(true);
      }
   }
}

