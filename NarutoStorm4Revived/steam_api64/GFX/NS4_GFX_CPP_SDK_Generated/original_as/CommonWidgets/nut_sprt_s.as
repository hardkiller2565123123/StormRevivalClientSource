package script.gauge_sprt_s
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public class nut_sprt_s extends MovieClip
   {
      
      public var mc_sprt:MovieClip;
      
      private const PALETTE_NUM:int = 4;
      
      internal var m_loader1:Array = new Array(this.PALETTE_NUM);
      
      internal var m_loader2:Array = new Array(this.PALETTE_NUM);
      
      internal var m_loader3:Array = new Array(this.PALETTE_NUM);
      
      internal var m_spIcon:Array = new Array(this.PALETTE_NUM);
      
      internal var m_spGauge:Array = new Array(this.PALETTE_NUM);
      
      internal var m_spEffect:Array = new Array(this.PALETTE_NUM);
      
      internal var m_dummy:Array = new Array(this.PALETTE_NUM);
      
      private var m_gaugeRateT:Number = 1;
      
      private var m_gaugeRateB:Number = 1;
      
      private var m_gaugeRateL:Number = 1;
      
      private var m_gaugeRateR:Number = 1;
      
      public function nut_sprt_s()
      {
         super();
         addFrameScript(23,this.frame24,39,this.frame40);
         var _loc1_:int = 0;
         while(_loc1_ < this.PALETTE_NUM)
         {
            this.m_loader1[_loc1_] = new ExtendLoader();
            this.m_loader1[_loc1_].visible = false;
            this.m_loader2[_loc1_] = new ExtendLoader();
            this.m_loader2[_loc1_].visible = false;
            this.m_loader3[_loc1_] = new ExtendLoader();
            this.m_loader3[_loc1_].visible = false;
            _loc1_++;
         }
         this.m_spIcon[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]);
         this.m_spIcon[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]);
         this.m_spIcon[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]);
         this.m_spIcon[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]);
         this.m_spGauge[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]["mc_gauge"]);
         this.m_spGauge[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]["mc_gauge"]);
         this.m_spGauge[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]["mc_gauge"]);
         this.m_spGauge[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]["mc_gauge"]);
         this.m_spEffect[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]["mc_eff_on"]);
         this.m_spEffect[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]["mc_eff_on"]);
         this.m_spEffect[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]["mc_eff_on"]);
         this.m_spEffect[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]["mc_eff_on"]);
         this.m_dummy[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]["dmy_sprt"]);
         this.m_dummy[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]["dmy_sprt"]);
         this.m_dummy[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]["dmy_sprt"]);
         this.m_dummy[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]["dmy_sprt"]);
      }
      
      public function Initialize() : *
      {
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:int = 0;
         var _loc3_:Number = NaN;
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         var _loc6_:MovieClip = null;
         if(this.visible)
         {
            _loc2_ = 0;
            while(_loc2_ < this.PALETTE_NUM)
            {
               _loc3_ = 1;
               if(this.m_spGauge[_loc2_])
               {
                  switch(_loc2_)
                  {
                     case 0:
                        _loc3_ = this.m_gaugeRateT;
                        break;
                     case 1:
                        _loc3_ = this.m_gaugeRateB;
                        break;
                     case 2:
                        _loc3_ = this.m_gaugeRateL;
                        break;
                     case 3:
                        _loc3_ = this.m_gaugeRateR;
                  }
                  _loc4_ = int(this.m_spGauge[_loc2_].totalFrames);
                  _loc5_ = _loc3_ * _loc4_;
                  this.m_spGauge[_loc2_].gotoAndStop(_loc5_);
               }
               if(this.m_spIcon[_loc2_])
               {
                  _loc6_ = MovieClip(this.m_spIcon[_loc2_]["mc_eff1"]);
                  if(_loc3_ == 1)
                  {
                     if(this.m_spIcon[_loc2_].currentLabel != "on")
                     {
                        this.m_spIcon[_loc2_].gotoAndStop("on");
                        if(_loc6_)
                        {
                           _loc6_.gotoAndPlay(1);
                        }
                     }
                     this.m_spGauge[_loc2_].visible = false;
                     this.m_spEffect[_loc2_].visible = true;
                  }
                  else
                  {
                     if(this.m_spIcon[_loc2_].currentLabel != "off")
                     {
                        this.m_spIcon[_loc2_].gotoAndStop("off");
                        if(_loc6_)
                        {
                           _loc6_.gotoAndPlay(1);
                        }
                     }
                     this.m_spGauge[_loc2_].visible = true;
                     this.m_spEffect[_loc2_].visible = false;
                  }
               }
               _loc2_++;
            }
         }
      }
      
      public function CreateSpSupportIcon(param1:int, param2:int, param3:String) : *
      {
         var loader:ExtendLoader = null;
         var url:URLRequest = null;
         var setMemberIdx:int = param1;
         var index:int = param2;
         var spSprtLabel:String = param3;
         loader = null;
         switch(setMemberIdx)
         {
            case 0:
               loader = ExtendLoader(this.m_loader1[index]);
               break;
            case 1:
               loader = ExtendLoader(this.m_loader2[index]);
               break;
            case 2:
               loader = ExtendLoader(this.m_loader3[index]);
         }
         switch(index)
         {
            case 0:
               url = new URLRequest("../charicon_sp/sp_" + spSprtLabel + "_t.xfbin");
               break;
            case 1:
               url = new URLRequest("../charicon_sp/sp_" + spSprtLabel + "_b.xfbin");
               break;
            case 2:
               url = new URLRequest("../charicon_sp/sp_" + spSprtLabel + "_l.xfbin");
               break;
            case 3:
               url = new URLRequest("../charicon_sp/sp_" + spSprtLabel + "_r.xfbin");
         }
         loader.unload();
         loader.load(url);
         loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
         loader.contentLoaderInfo.addEventListener(Event.COMPLETE,function(param1:Event):void
         {
            m_dummy[index].addChild(loader);
            m_dummy[index].scaleX = 1.5;
            m_dummy[index].scaleY = 1.5;
         });
      }
      
      public function SetSpSupportIcon(param1:int) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < this.PALETTE_NUM)
         {
            this.m_loader1[_loc2_].visible = false;
            this.m_loader2[_loc2_].visible = false;
            this.m_loader3[_loc2_].visible = false;
            switch(param1)
            {
               case 0:
                  this.m_loader1[_loc2_].visible = true;
                  break;
               case 1:
                  this.m_loader2[_loc2_].visible = true;
                  break;
               case 2:
                  this.m_loader3[_loc2_].visible = true;
            }
            _loc2_++;
         }
      }
      
      public function SetIconNum(param1:Boolean) : *
      {
         var _loc2_:MovieClip = MovieClip(this["mc_sprt"]);
         if(_loc2_)
         {
            if(param1)
            {
               _loc2_.gotoAndStop("sp4");
            }
            else
            {
               _loc2_.gotoAndStop("sp2");
            }
            this.m_spIcon[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]);
            this.m_spIcon[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]);
            this.m_spIcon[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]);
            this.m_spIcon[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]);
            this.m_spGauge[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]["mc_gauge"]);
            this.m_spGauge[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]["mc_gauge"]);
            this.m_spGauge[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]["mc_gauge"]);
            this.m_spGauge[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]["mc_gauge"]);
            this.m_spEffect[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]["mc_eff_on"]);
            this.m_spEffect[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]["mc_eff_on"]);
            this.m_spEffect[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]["mc_eff_on"]);
            this.m_spEffect[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]["mc_eff_on"]);
            this.m_dummy[0] = MovieClip(this["mc_sprt"]["mc_sp_t"]["dmy_sprt"]);
            this.m_dummy[1] = MovieClip(this["mc_sprt"]["mc_sp_b"]["dmy_sprt"]);
            this.m_dummy[2] = MovieClip(this["mc_sprt"]["mc_sp_l"]["dmy_sprt"]);
            this.m_dummy[3] = MovieClip(this["mc_sprt"]["mc_sp_r"]["dmy_sprt"]);
         }
      }
      
      public function SetGaugeRate(param1:int, param2:Number) : *
      {
         switch(param1)
         {
            case 0:
               this.m_gaugeRateT = param2;
               break;
            case 1:
               this.m_gaugeRateB = param2;
               break;
            case 2:
               this.m_gaugeRateL = param2;
               break;
            case 3:
               this.m_gaugeRateR = param2;
         }
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
      
      internal function frame24() : *
      {
         this.stop();
      }
      
      internal function frame40() : *
      {
         this.stop();
      }
   }
}

