package net_rank_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class smb_wins_per_9 extends MovieClip
   {
      
      public var txt_per:smb_font;
      
      public var txt_wins:smb_font;
      
      public function smb_wins_per_9()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_wins.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_wins.SetTextSize(25);
         this.txt_wins.SetTextColor(12305407);
         this.txt_wins.SetTextFieldWidth(260);
         this.txt_wins.SetTextFit(true);
         this.txt_per.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_per.SetTextSize(25);
         this.txt_per.SetTextColor(12305407);
         this.txt_per.SetTextFieldWidth(260);
         this.txt_per.SetTextFit(true);
      }
   }
}

