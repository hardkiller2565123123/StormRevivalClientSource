package freebtl_leag_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public dynamic class smb_list_mark_round_9 extends MovieClip
   {
      
      public var txt_round:smb_font;
      
      public function smb_list_mark_round_9()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_round.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_round.SetTextColor(6520706);
         this.txt_round.SetTextSize(smb_font.CCD_FONT_SIZE_LARGE);
         this.txt_round.SetText("1");
      }
   }
}

