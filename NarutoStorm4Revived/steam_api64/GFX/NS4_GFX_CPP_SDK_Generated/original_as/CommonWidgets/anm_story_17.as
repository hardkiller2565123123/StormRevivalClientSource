package start_memory_fla
{
   import flash.display.MovieClip;
   import script.tips.anm_page;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   import script.xcp_bg1.smb_bg1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol43")]
   public dynamic class anm_story_17 extends MovieClip
   {
      
      public var dmy_img:nut_tex00;
      
      public var mc_bg1:smb_bg1;
      
      public var mc_page:anm_page;
      
      public var txt_story:smb_font;
      
      public var txt_title:smb_font;
      
      public function anm_story_17()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_story.SetText("あらすじ内容＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊");
         this.txt_title.SetText("あらすじ_gy");
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextSize(29);
         this.txt_story.SetTextSize(27);
         this.txt_story.SetTextColor(4467231);
         this.txt_story.SetTextFieldWidth(800);
         this.txt_story.SetTextWordWrap(true);
         this.txt_story.SetTextStandardAlignByLanguage();
      }
   }
}

