package script.freebtl_prac_lst
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_prac_list extends MovieClip
   {
      
      internal static const LIST_MAX_NUM:int = 5;
      
      public var mc_prac_bar00:MovieClip;
      
      public var GetListNum:Function;
      
      public var GetParam:Function;
      
      public var RequestNext:Function;
      
      public var SetFinish:Function;
      
      internal var m_listNum:int;
      
      internal var m_checkNo:int;
      
      internal var m_successNum:int;
      
      internal var m_listParam:Array;
      
      internal var m_isAnm:Boolean;
      
      internal var m_wait:int;
      
      public function nut_prac_list()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
      }
      
      public function Initialize() : *
      {
         var _loc1_:int = 0;
         var _loc2_:Object = null;
         trace("!--- call Initialize()");
         this.m_listNum = this.GetListNum();
         trace("list num = " + this.m_listNum);
         this.m_listParam = new Array(this.m_listNum);
         trace("param num = " + this.m_listParam.length);
         this.m_checkNo = -1;
         this.m_successNum = 0;
         this.m_isAnm = false;
         this.m_wait = 0;
         this.mc_prac_bar00.mc_check.gotoAndStop("check_off");
         this.mc_prac_bar00.gotoAndStop("off");
         _loc1_ = 0;
         while(_loc1_ < this.m_listNum)
         {
            _loc2_ = new Object();
            this.GetParam(_loc1_,_loc2_);
            this.SetParam(_loc1_,_loc2_);
            _loc1_++;
         }
         this.SetupPlate(0);
         gotoAndStop("in");
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         visible = param1;
      }
      
      public function Open() : *
      {
         gotoAndPlay("in");
      }
      
      public function Close() : *
      {
         gotoAndPlay("out");
      }
      
      public function UpdateParam(param1:int) : *
      {
         var _loc2_:Object = new Object();
         this.GetParam(param1,_loc2_);
         this.SetParam(param1,_loc2_);
         this.SetupPlate(param1);
      }
      
      public function SetSuccessIcon(param1:int) : *
      {
         this.mc_prac_bar00.mc_check.gotoAndPlay("enter");
         this.m_checkNo = param1;
         this.m_isAnm = true;
         ExternalInterface.call("RequestPlaySE",int(22));
      }
      
      private function onEnterFrameCtrl(param1:Event) : *
      {
         if(this.m_isAnm)
         {
            if(currentFrameLabel == "loop_on" && this.mc_prac_bar00.mc_check.currentFrameLabel == "check_on")
            {
               if(this.m_wait < 30)
               {
                  ++this.m_wait;
               }
               else
               {
                  this.m_wait = 0;
                  gotoAndPlay("out");
                  ExternalInterface.call("RequestPlaySE",int(0));
               }
            }
            if(currentFrameLabel == "end")
            {
               ++this.m_successNum;
               if(this.m_successNum >= this.m_listNum)
               {
                  this.SetFinish();
                  removeEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
                  return;
               }
               this.SetupPlate(this.m_successNum);
               gotoAndPlay("in");
               ExternalInterface.call("RequestPlaySE",int(0));
            }
            if(currentFrameLabel == "loop_on" && this.mc_prac_bar00.mc_check.currentFrameLabel == "check_off")
            {
               this.m_isAnm = false;
               this.SetupPlate(this.m_successNum);
               this.RequestNext();
            }
         }
      }
      
      private function SetParam(param1:int, param2:Object) : *
      {
         this.m_listParam[param1] = param2;
      }
      
      private function SetupPlate(param1:int) : *
      {
         this.mc_prac_bar00.txt_prac.SetText(this.m_listParam[param1].title);
         this.mc_prac_bar00.txt_cmd.SetText(this.m_listParam[param1].command);
         this.mc_prac_bar00.txt_cnt.SetText(this.m_listParam[param1].objective);
         this.mc_prac_bar00.mc_check.gotoAndStop("check_off");
      }
      
      public function SetPlateText(param1:Object) : *
      {
         if(param1.title != "")
         {
            this.mc_prac_bar00.txt_prac.SetText(param1.title);
         }
         if(param1.command != "")
         {
            this.mc_prac_bar00.txt_cmd.SetText(param1.command);
         }
         if(param1.objective != "")
         {
            this.mc_prac_bar00.txt_cnt.SetText(param1.objective);
         }
      }
      
      internal function frame6() : *
      {
         this.stop();
      }
      
      internal function frame11() : *
      {
         this.stop();
      }
   }
}

