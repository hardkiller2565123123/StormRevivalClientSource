package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public dynamic class smb_suc_23 extends MovieClip
   {
      
      public var txt_suc:smb_font;
      
      public function smb_suc_23()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_suc.SetTextSize(28);
         this.txt_suc.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_suc.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
   }
}

