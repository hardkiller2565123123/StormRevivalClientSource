package net_card_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol44")]
   public dynamic class smb_rank_title_26 extends MovieClip
   {
      
      public var txt_rank_title:smb_font;
      
      public function smb_rank_title_26()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rank_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rank_title.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_rank_title.SetTextSize(28);
         this.txt_rank_title.SetTextFieldWidth(400);
         this.txt_rank_title.SetTextFit(true);
      }
   }
}

