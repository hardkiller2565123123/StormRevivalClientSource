package net_match_2_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class anm_wins_8 extends MovieClip
   {
      
      public var mc_base:MovieClip;
      
      public var txt_wins:smb_font;
      
      public function anm_wins_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_wins.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_wins.SetTextSize(29);
         this.txt_wins.SetTextColor(13042178);
      }
   }
}

