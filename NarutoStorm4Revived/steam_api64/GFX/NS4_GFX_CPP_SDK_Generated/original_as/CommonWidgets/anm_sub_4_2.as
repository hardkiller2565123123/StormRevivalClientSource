package start_evnt_s_fla
{
   import flash.display.MovieClip;
   import script.icon_navi.nut_navi;
   import script.icon_new.nut_new;
   import script.icon_new.nut_none;
   import script.icon_result2.smb_rslt_ok;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol31")]
   public dynamic class anm_sub_4 extends MovieClip
   {
      
      public var dmy_char:nut_tex00;
      
      public var mc_navi:nut_navi;
      
      public var mc_new:nut_new;
      
      public var mc_now:MovieClip;
      
      public var mc_num:MovieClip;
      
      public var mc_ok:smb_rslt_ok;
      
      public var mc_qtn:nut_none;
      
      public function anm_sub_4()
      {
         super();
         addFrameScript(0,this.frame1,29,this.frame30,30,this.frame31,31,this.frame32,79,this.frame80,80,this.frame81,81,this.frame82,109,this.frame110,110,this.frame111);
      }
      
      internal function frame1() : *
      {
      }
      
      internal function frame30() : *
      {
         gotoAndPlay("on");
      }
      
      internal function frame31() : *
      {
         this.stop();
      }
      
      internal function frame32() : *
      {
         this.stop();
      }
      
      internal function frame80() : *
      {
         this.stop();
      }
      
      internal function frame81() : *
      {
         this.stop();
      }
      
      internal function frame82() : *
      {
         this.stop();
      }
      
      internal function frame110() : *
      {
         gotoAndPlay("sel");
      }
      
      internal function frame111() : *
      {
         gotoAndPlay("sel");
      }
   }
}

