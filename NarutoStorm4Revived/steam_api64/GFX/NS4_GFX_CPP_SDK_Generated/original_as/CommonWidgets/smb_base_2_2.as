package load_story_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_line;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class smb_base_2 extends MovieClip
   {
      
      public var all_line:nut_line;
      
      public var txt_title:smb_font;
      
      public var txt_story:smb_font;
      
      public function smb_base_2()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetTextSize(38);
         this.txt_story.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_story.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_story.SetTextSize(33);
      }
   }
}

