package hist_cmn_fla
{
   import flash.display.MovieClip;
   import script.icon_new.nut_new;
   import script.icon_rate_s.nut_rate_s;
   import script.icon_up.nut_up1;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol24")]
   public dynamic class anm_btl_c_19 extends MovieClip
   {
      
      public var dmy_char1:nut_tex00;
      
      public var dmy_char2:nut_tex00;
      
      public var mc_new:nut_new;
      
      public var mc_rslt:nut_rate_s;
      
      public var mc_type:MovieClip;
      
      public var mc_up:nut_up1;
      
      public var txt_none:smb_font;
      
      public function anm_btl_c_19()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,29,this.frame30,44,this.frame45,45,this.frame46);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_none.SetTextSize(30);
         this.txt_none.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_none.DisableDropShadowFilter();
         this.txt_none.SetTextColor(16777215);
      }
      
      internal function frame2() : *
      {
         this.txt_none.SetDropShadowFilter(16771214);
         this.txt_none.SetTextColor(8653824);
      }
      
      internal function frame30() : *
      {
         gotoAndPlay("on");
      }
      
      internal function frame45() : *
      {
         this.stop();
      }
      
      internal function frame46() : *
      {
         this.stop();
         this.txt_none.DisableDropShadowFilter();
         this.txt_none.SetTextColor(921102);
      }
   }
}

