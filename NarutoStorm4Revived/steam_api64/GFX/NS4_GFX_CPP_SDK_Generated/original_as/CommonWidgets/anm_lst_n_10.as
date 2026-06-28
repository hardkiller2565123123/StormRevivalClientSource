package hist_cmn_fla
{
   import flash.display.MovieClip;
   import script.icon_new.nut_new;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class anm_lst_n_10 extends MovieClip
   {
      
      public var mc_new:nut_new;
      
      public var txt_msg:smb_font;
      
      public function anm_lst_n_10()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,29,this.frame30,30,this.frame31,44,this.frame45,45,this.frame46);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_msg.SetTextSize(30);
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_msg.SetTextFieldWidth(597);
         this.txt_msg.SetTextScroll(true);
         this.txt_msg.SetTextColor(16777215);
         this.txt_msg.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_msg.StopTextScroll();
      }
      
      internal function frame2() : *
      {
         this.txt_msg.SetDropShadowFilter(16771214);
         this.txt_msg.SetTextColor(8653824);
         this.txt_msg.PlayTextScroll();
      }
      
      internal function frame30() : *
      {
         gotoAndPlay("on");
      }
      
      internal function frame31() : *
      {
         this.txt_msg.StopTextScroll();
      }
      
      internal function frame45() : *
      {
         this.stop();
      }
      
      internal function frame46() : *
      {
         this.stop();
         this.txt_msg.DisableDropShadowFilter();
         this.txt_msg.SetTextColor(921102);
         this.txt_msg.StopTextScroll();
      }
   }
}

