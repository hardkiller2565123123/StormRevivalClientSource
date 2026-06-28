package hist_cmn_brt_fla
{
   import flash.display.MovieClip;
   import script.icon_new.nut_new;
   import script.icon_rate_s.nut_rate_s;
   import script.icon_up.nut_up1;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol45")]
   public dynamic class anm_lst_11 extends MovieClip
   {
      
      public var dmy_char1:nut_tex00;
      
      public var dmy_char2:nut_tex00;
      
      public var mc_msg:MovieClip;
      
      public var mc_new:nut_new;
      
      public var mc_rslt:nut_rate_s;
      
      public var mc_type:MovieClip;
      
      public var mc_up:nut_up1;
      
      public function anm_lst_11()
      {
         super();
         addFrameScript(0,this.frame1,29,this.frame30,44,this.frame45,45,this.frame46,46,this.frame47,75,this.frame76,90,this.frame91,91,this.frame92);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame30() : *
      {
         gotoAndPlay("on_btl");
      }
      
      internal function frame45() : *
      {
         this.stop();
      }
      
      internal function frame46() : *
      {
         this.stop();
      }
      
      internal function frame47() : *
      {
         this.stop();
      }
      
      internal function frame76() : *
      {
         gotoAndPlay("on_mov");
      }
      
      internal function frame91() : *
      {
         this.stop();
      }
      
      internal function frame92() : *
      {
         this.stop();
      }
   }
}

